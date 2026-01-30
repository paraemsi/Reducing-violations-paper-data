#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.12"
# dependencies = [
#   "aider-chat==0.86.1",
#   "typer",
#   "json5",
#   "packaging",
#   "pyyaml",
#   "pillow",
#   "requests",
#   "oslex",
#   "mixpanel",
#   "posthog",
#   "pyperclip",
#   "prompt_toolkit",
#   "pydub",
#   "importlib_resources",
#   "pathspec",
#   "pexpect",
#   "psutil",
#   "pypandoc",
#   "grep_ast",
#   "diskcache",
#   "tqdm",
#   "diff_match_patch",
#   "litellm",
# ]
# ///

"""
Export aider chat history to LLM conversation format (JSON).

This script loads an aider chat history file and exports the complete
conversation as sent to the LLM, including system prompts, file content,
repository maps, and all messages with tool calls.
"""

import json
import re
from pathlib import Path
from typing import Optional

import typer
from aider.coders import Coder
from aider.io import InputOutput
from aider.models import Model

app = typer.Typer(
    help="Export aider chat history to LLM conversation format (JSON).",
    add_completion=False,
)


def parse_history_header(history_path: Path) -> dict:
    """
    Parse the header of an aider chat history file to extract metadata.

    Returns a dict with keys: main_model, edit_format, weak_model, started_at
    """
    metadata: dict = {}

    with history_path.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()

            # Stop at first non-header line (empty line or first user message)
            if not line or (line.startswith("#") and "aider chat started" not in line):
                if metadata:  # If we've already found metadata, stop
                    break

            # Parse "# aider chat started at ..."
            if line.startswith("# aider chat started at"):
                match = re.search(r"at (.+)$", line)
                if match:
                    metadata["started_at"] = match.group(1)

            # Parse "> Main model: ... with ... edit format"
            elif line.startswith("> Main model:"):
                match = re.search(r"Main model:\s+(\S+)\s+with\s+(\S+)\s+edit format", line)
                if match:
                    metadata["main_model"] = match.group(1)
                    metadata["edit_format"] = match.group(2)

            # Parse "> Weak model: ..."
            elif line.startswith("> Weak model:"):
                match = re.search(r"Weak model:\s+(\S+)", line)
                if match:
                    metadata["weak_model"] = match.group(1)

    return metadata


def get_fnames_from_testdir(testdir: Path, original_polyglot_root: Path | None) -> list[str]:
    """Get list of filenames in the test directory.

    This piece of code uses logic directly from aider benchmark.py file.
    """
    # Read solution and test files from config
    fnames = []
    config_file = testdir / ".meta/config.json"
    if not config_file.exists():
        raise ValueError(f"No config file found: {config_file}")

    with open(config_file) as f:
        config = json.loads(f.read())

    # Get file sets from config
    test_files = config.get("files", {}).get("test", [])
    example_files = config.get("files", {}).get("example", [])
    solution_files = set(config.get("files", {}).get("solution", []))

    # Forcibly ignore certain files not covered by test_files and example_files
    ignore_files = set(
        [
            "CMakeLists.txt",
            "Cargo.toml",
        ]
    )

    # Add all files under .meta and .docs directories
    ignore_files.update(str(p.relative_to(testdir)) for p in testdir.glob(".meta/**/*"))
    ignore_files.update(str(p.relative_to(testdir)) for p in testdir.glob(".docs/**/*"))

    # Also ignore test & example files
    ignore_files.update(test_files)
    ignore_files.update(example_files)

    # Remove any ignore files from the solution set that LLM will edit
    solution_files.difference_update(ignore_files)

    for file_path in solution_files:
        if original_polyglot_root:
            lang_part = str(testdir).split("/exercises/practice/")[0]
            original_fname = (
                    original_polyglot_root
                    / Path(lang_part).name
                    / "exercises"
                    / "practice"
                    / testdir.name
                    / file_path
                )
            src = original_fname
        else:
            src = testdir / Path(file_path)
        if src.exists():
            fnames.append(src)
        else:
            print(f"Warning: Solution file not found: {src}")

    return fnames



def load_and_export_conversation(
    history_path: Path,
    output_path: Path,
    original_polyglot_root: Path | None,
    model: Optional[str] = None,
) -> None:
    """
    Load aider chat history and export complete conversation to JSON.

    Args:
        history_path: Path to .aider.chat.history.md file
        output_path: Path to output JSON file
        model: Optional model name to use for loading
    """
    # Validate history file exists
    if not history_path.exists():
        typer.echo(f"Error: History file not found: {history_path}", err=True)
        raise typer.Exit(code=1)

    # Parse history header to extract metadata
    metadata = parse_history_header(history_path)

    # Use model from header if not specified by user
    if not model and "main_model" in metadata:
        model = metadata["main_model"]
        typer.echo(f"Detected model from history: {model}")

    if "weak_model" in metadata:
        typer.echo(f"Detected weak model from history: {metadata['weak_model']}")

    if "edit_format" in metadata:
        typer.echo(f"Detected edit format from history: {metadata['edit_format']}")

    # Create minimal IO to avoid interactive prompts
    io = InputOutput(
        yes=True,  # Auto-confirm all prompts
        chat_history_file=str(history_path),
    )

    fnames = get_fnames_from_testdir(history_path.parent, original_polyglot_root)
    typer.echo(f"Preloaded {fnames} solution files from test directory.")

    # Prepare coder kwargs
    coder_kwargs = {
        "io": io,
        "restore_chat_history": True,
        "auto_commits": False,
        "dirty_commits": False,
        "auto_lint": False,
        "use_git": False,
        "fnames": fnames,
    }

    if model:
        coder_kwargs["main_model"] = Model(model)

    try:
        # Create coder instance and load history
        typer.echo(f"Loading chat history from: {history_path}")
        coder = Coder.create(**coder_kwargs)

        # Extract all messages - done_messages contains the restored history
        typer.echo("Extracting conversation messages...")

        # IMPORTANT: Get the conversation history FIRST (before format_messages() moves them)
        # format_messages() modifies coder's internal state and may clear these lists
        conversation_done = list(coder.done_messages)
        conversation_cur = list(coder.cur_messages)

        # Now get all the other chunks (system, examples, repo, chat_files, etc.)
        chunks = coder.format_messages()

        # Manually build the complete message list in the correct order for export.
        # The proper order for analyzing an LLM conversation is:
        # 1. All system prompts/rules (so rules are established before use)
        # 2. File content (so files are introduced before being edited)
        # 3. Conversation history (the actual user/assistant interaction)
        #
        # Note: We do NOT use chunks.done/chunks.cur because format_messages()
        # may have cleared or modified them. We use our saved copies instead.
        all_messages = (
            chunks.system           # Main system prompt with general instructions
            + chunks.reminder       # Detailed rules (e.g., SEARCH/REPLACE format) - MUST come before conversation!
            + chunks.examples       # Example conversations (if any)
            + chunks.readonly_files # Read-only file context (if any)
            + chunks.repo           # Repository map (if any)
            + chunks.chat_files     # File content introduction (must come before edits in conversation)
            + conversation_done     # Conversation history (from saved copy)
            + conversation_cur      # Current messages (from saved copy)
        )

        if not all_messages:
            typer.echo("Warning: No messages found in history.", err=True)
        else:
            # Count different message types for diagnostic purposes
            system_count = len(chunks.system)
            examples_count = len(chunks.examples)
            repo_count = len(chunks.repo)
            readonly_count = len(chunks.readonly_files)
            chat_files_count = len(chunks.chat_files)
            done_count = len(conversation_done)
            cur_count = len(conversation_cur)
            reminder_count = len(chunks.reminder)

            typer.echo(
                f"Found {len(all_messages)} total messages:\n"
                f"  - {system_count} system\n"
                f"  - {examples_count} examples\n"
                f"  - {readonly_count} readonly_files\n"
                f"  - {repo_count} repo\n"
                f"  - {done_count} done (conversation history)\n"
                f"  - {chat_files_count} chat_files (contains file content)\n"
                f"  - {cur_count} cur\n"
                f"  - {reminder_count} reminder"
            )

        # Export to JSON
        typer.echo(f"Exporting to: {output_path}")
        with output_path.open("w", encoding="utf-8") as f:
            json.dump(all_messages, f, indent=2, ensure_ascii=False)

        typer.echo(f"Successfully exported {len(all_messages)} messages to {output_path}")

    except Exception as e:
        typer.echo(f"Error: Failed to process chat history: {e}", err=True)
        raise typer.Exit(code=1)


@app.command()
def main(
    history_path: Path = typer.Argument(
        ...,
        help="Path to .aider.chat.history.md file",
        exists=True,
        dir_okay=False,
        resolve_path=True,
    ),
    output: Path = typer.Option(
        "conversation.json",
        "--output",
        "-o",
        help="Output JSON file path",
        resolve_path=True,
    ),
    original_polyglot_root: Optional[Path] = typer.Option(
        None,
        "--original-polyglot-root",
        help="Path to original polyglot root for original file content",
        resolve_path=True,
    ),
    model: Optional[str] = typer.Option(
        None,
        "--model",
        "-m",
        help="Optional model name to use (e.g., 'gpt-4', 'claude-3-opus')",
    ),
) -> None:
    """
    Export aider chat history to LLM conversation format.

    The output JSON contains the complete conversation as sent to the LLM,
    including system prompts, file content, repository maps, and all messages
    with tool/function calls.

    Example usage:

        python export_aider_conversation.py .aider.chat.history.md

        python export_aider_conversation.py .aider.chat.history.md -o output.json

        python export_aider_conversation.py .aider.chat.history.md -m gpt-4
    """
    load_and_export_conversation(history_path, output, original_polyglot_root, model)


if __name__ == "__main__":
    app()
