#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.12"
# dependencies = [
#   "aider",
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


def load_and_export_conversation(
    history_path: Path,
    output_path: Path,
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

    # Prepare coder kwargs
    coder_kwargs = {
        "io": io,
        "restore_chat_history": True,
        "auto_commits": False,
        "dirty_commits": False,
        "auto_lint": False,
    }

    if model:
        coder_kwargs["main_model"] = Model(model)

    try:
        # Create coder instance and load history
        typer.echo(f"Loading chat history from: {history_path}")
        coder = Coder.create(**coder_kwargs)

        # Extract all messages - done_messages contains the restored history
        typer.echo("Extracting conversation messages...")

        # Get the conversation history FIRST (before format_messages() moves them)
        conversation_messages = coder.done_messages + coder.cur_messages

        # Get system prompts from format_messages()
        chunks = coder.format_messages()
        system_messages = chunks.system if hasattr(chunks, "system") and chunks.system else []

        # Combine: system prompts first, then conversation
        all_messages = system_messages + conversation_messages

        if not all_messages:
            typer.echo("Warning: No messages found in history.", err=True)
        else:
            system_count = len(system_messages)
            conv_count = len(conversation_messages)
            typer.echo(
                f"Found {len(all_messages)} messages ({system_count} system, {conv_count} conversation)"
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
    load_and_export_conversation(history_path, output, model)


if __name__ == "__main__":
    app()
