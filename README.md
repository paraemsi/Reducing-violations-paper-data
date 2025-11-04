# Cutting MISRA C++:2023 violations in LLM-generated code by up to 83% with prompt engineering

This repository contains the supplementary materials, experimental data, and artifacts for the paper **"Cutting MISRA C++:2023 violations in LLM-generated code by up to 83% with prompt engineering"**.

## Repository Contents

### [`prompts/`](prompts/)

Contains distilled MISRA C++:2023 compliance instructions targeting the most frequently violated rules:

- **[`top10-o3.txt`](prompts/top10-o3.txt)** (8.9 KB): Complete set of succinct, actionable instructions for the top-10 most violated MISRA C++:2023 rules. These instructions were derived through LLM-assisted distillation of verbose MISRA rule documentation and formatted for direct integration into code generation prompts.

- **[`misra_compliance_instruction_prompt_template.txt`](prompts/misra_compliance_instruction_prompt_template.txt)** (1.0 KB): Template prompt used with o3 to distill verbose MISRA C++:2023 rule documentation into concise, actionable bullet-point instructions. This template can be reused to create compliance instructions for other coding standards with verbose documentation.

### [`experiments_data/`](experiments_data/)

Comprehensive experimental results from all baseline and intervention runs:

#### [`all_violations.csv`](experiments_data/all_violations.csv) (14 MB, 42,556 rows)

MISRA C++:2023 violation data from static analysis. Each row represents a single rule violation detected by Parasoft C/C++test.

**Key columns:**
- `experiment`: Experiment arm (e.g., "Baseline GPT-4.1", "Top-5 o3")
- `build_id`: Unique identifier for each experimental run
- `testcase`: Name of the benchmark programming task
- `severity`: Violation severity (2=Required, 4=Advisory)
- `rule.id`: MISRA C++:2023 rule identifier (e.g., MISRACPP2023-6_9_2-a)
- `rule.category.description`: Rule textual description
- `finding.resource.searchPath`: Source file containing the violation
- `finding.region.startLine/endLine`: Location of violation in source code

#### [`all_functional_tests.csv`](experiments_data/all_functional_tests.csv) (690 KB, 5,357 rows)

Functional test results and code metrics for each testcase attempt across all experimental runs reported by the aider polyglot benchmark framework.

**Key columns:**
- `experiment`: Experiment arm
- `build_id`: Unique run identifier
- `model`: LLM model identifier
- `testcase`: Benchmark task name
- `cost`: API cost in USD for generating the solution as reported by aider
- `duration`: Time in seconds to complete the task
- `prompt_tokens`/`completion_tokens`: Token usage statistics
- `pass2`: Boolean indicating whether all unit tests passed (after up to 2 attempts)
- `compiled`: Boolean indicating successful compilation
- `loc`: Lines of code
- `testcase_violations`: Total MISRA violations detected
- `violations per KLOC`: Normalized violation rate (violations per 1000 lines of code)

### [`polyglot_artifacts/`](polyglot_artifacts/)

Contains 208 directories with LLM-generated C++ code samples from all experimental runs. Each directory represents one complete execution of the 26-task benchmark suite.

**Directory naming convention:**
```
YYYY-MM-DD-HH-MM-SS--[experiment_type].[iteration_number]
```

**Examples:**
- `2025-08-21-08-38-37--misracpp_baseline.01`: First baseline run
- `2025-09-01-23-07-05--cpp_misra_o3.top10.18`: o3 model with Top-10 rules, iteration 18

**Directory structure:**
```
<timestamp>--<experiment>.<iteration>/
├── cpp/
│   └── exercises/
│       └── practice/
│           ├── <testcase_name>/
│           │   ├── .aider.chat.history.md   # Aider interaction log
│           │   ├── .aider.results.json      # Test results (pass/fail, errors)
│           │   ├── <testcase_name>.cpp      # Generated solution
│           │   ├── <testcase_name>.h        # Header file (if applicable)
│           │   ├── <testcase_name>_test.cpp # Unit tests
│           │   └── .docs/
│           │       ├── instructions.md      # Problem specification
│           │       └── introduction.md      # Problem context
│           └── [25 more testcases...]
```

## Experimental Design

### Models Evaluated

**Comprehensive evaluation (20 runs per condition):**
- DeepSeek Chat v3.1
- GPT-4.1
- GPT-5
- o3

**Exploratory evaluation (1 run per condition):**
- Claude Opus 4.1
- Gemini 2.5 Pro
- Grok Code Fast 1

### Intervention Arms

- **Baseline**: No MISRA-specific instructions
- **Top-3**: Instructions for the 3 most frequently violated rules (GPT-4.1, DeepSeek Chat v3.1)
- **Top-5**: Instructions for the 5 most frequently violated rules (DeepSeek Chat v3.1, GPT-5, o3, plus all exploratory models)
- **Top-10**: Instructions for the 10 most frequently violated rules (o3 only)

### Benchmark Tasks

26 algorithmically challenging C++ tasks from the [aider polyglot benchmark](https://aider.chat/docs/leaderboards/), ranging from basic algorithmic problems to more complex software engineering tasks. Each testcase includes comprehensive unit tests for correctness validation.

### Methodology

- **Design**: Before-after, repeated-measures quasi-experimental design
- **Unit of inference**: Per-testcase aggregated metrics (N=26 testcases)
- **Repetitions**: 20 independent runs per model-condition combination for comprehensive evaluation
- **Total testcase attempts**: 2,080 baseline + matched intervention attempts = 4,160+ attempts
- **Static analysis**: Parasoft C/C++test 2025.1.0 with complete MISRA C++:2023 ruleset (179 guidelines)
- **Compiler**: g++ 11.4.0 targeting C++17
- **Code generation tool**: aider v0.86.2.dev1+g32faf82b3.d20250820 (AI pair programming assistant)

## Key Results

### Baseline Compliance Patterns (RQ1)

All evaluated models generated code with similar baseline violation rates:
- o3: 23.64 violations/KLOC (95% CI: 17.36-32.17)
- GPT-5: 23.70 violations/KLOC (95% CI: 16.95-31.90)
- GPT-4.1: 25.01 violations/KLOC (95% CI: 16.71-43.50)
- DeepSeek Chat v3.1: 29.28 violations/KLOC (95% CI: 20.67-53.33)

**Top-5 most violated rules (shared across all models):**
1. MISRACPP2023-6_9_2-a (Advisory): Avoid standard integer type names (~30-33% of violations)
2. MISRACPP2023-8_0_1-b (Advisory): Use parentheses for operator precedence (~12-19%)
3. MISRACPP2023-7_0_6-a (Required): Appropriate numeric type assignments (~6-21%)
4. MISRACPP2023-9_3_1-b (Required): Use compound statements for loops/conditionals (~7-11%)
5. MISRACPP2023-7_0_3-a (Required): Avoid character numerical values (~6-12%)

### Intervention Effectiveness (RQ2)

All intervention conditions produced statistically significant reductions in violations (paired permutation tests, all p < 0.01):

| Model              | Top-3 Reduction | Top-5 Reduction | Top-10 Reduction |
|--------------------|-----------------|-----------------|------------------|
| DeepSeek Chat v3.1 | 44.47%          | 57.07%          | —                |
| GPT-4.1            | 56.63%          | —               | —                |
| GPT-5              | —               | 81.08%          | —                |
| o3                 | —               | 74.68%          | 83.36%           |

**Post-intervention violation rates:**
- o3 (Top-10): 3.93 violations/KLOC
- GPT-5 (Top-5): 4.48 violations/KLOC
- o3 (Top-5): 5.98 violations/KLOC
- GPT-4.1 (Top-3): 10.89 violations/KLOC
- DeepSeek (Top-5): 12.57 violations/KLOC
- DeepSeek (Top-3): 16.26 violations/KLOC

### Functional Trade-offs (RQ3)

Most model-intervention combinations maintained functional correctness:
- **Minimal impact**: GPT-5 and o3 with Top-5 instructions showed small, non-significant changes in pass rates (Δ ≈ -1 to -3 percentage points, p > 0.05)
- **Significant declines**: GPT-4.1 (Top-3) showed 25.65% relative pass rate decline (p = 0.016); o3 (Top-10) showed 10.02% relative decline (p = 0.041)
- **Dose-response pattern**: Larger intervention scopes associated with greater functional impact, varying by model capacity

## How to Use This Repository

### Exploring the Data

1. **Review compliance instructions**: Start with `prompts/top10-o3.txt` to see example distilled MISRA rules
2. **Analyze violation patterns**: Load `experiments_data/all_violations.csv` to examine which rules are violated and where
3. **Compare functional metrics**: Use `experiments_data/all_functional_tests.csv` to assess compile rates, pass rates, and costs across conditions
4. **Inspect generated code**: Browse `polyglot_artifacts/` to examine actual LLM-generated solutions and aider interaction logs

### Using the Prompts in Your Projects

The distilled MISRA instructions in `prompts/top10-o3.txt` can be directly integrated into your LLM prompts:

1. Copy the relevant rule instructions from the file
2. Append them to your code generation prompt with context like:
   ```
   In newly generated code obey the following MISRA C++ rules:

   <rules>
   [paste distilled instructions here]
   </rules>
   ```
3. Start with Top-3 or Top-5 rules for minimal functional impact
4. Monitor compile and pass rates before expanding to broader rule sets

### Reproducing the Experiments

To reproduce or extend this research:

1. **Modified benchmark framework**: [https://github.com/paraemsi/polyglot-benchmark](https://github.com/paraemsi/polyglot-benchmark)
   - Includes MISRA C++:2023 compliance checking via Parasoft C/C++test
   - CMakeLists.txt modified to invoke static analysis after compilation

2. **Aider integration patch**: [https://gist.github.com/paraemsi/6ac59bf2d3583f3a16efaa0798e146fc](https://gist.github.com/paraemsi/6ac59bf2d3583f3a16efaa0798e146fc)
   - Adds `--additional-instructions-file` parameter to aider benchmark script
   - Enables injection of compliance instructions into prompts

3. **Tool versions**:
   - aider: v0.86.2.dev1+g32faf82b3.d20250820
   - Parasoft C/C++test: 2025.1.0
   - g++: 11.4.0
   - C++ standard: C++17

### Creating Custom Distilled Instructions

Use the template in `prompts/misra_compliance_instruction_prompt_template.txt` to distill other MISRA rules or coding standards:

1. Extract verbose rule documentation from your static analysis tool
2. Replace `{rule_str}` in the template with the rule text
3. Use an LLM (e.g., o3, GPT-5) to generate concise bullet-point instructions
4. Review and refine the output for clarity and actionability

## Practical Recommendations

Based on the empirical findings, we recommend a **step-up prompting strategy**:

1. **Start small**: Begin with Top-3 or Top-5 rules targeting your model's most frequent violations
2. **Monitor continuously**: Track compile rates and pass rates separately for each testcase
3. **Expand cautiously**: Only increase intervention scope when functional metrics remain stable
4. **Model-aware limits**: Recognize that weaker models may struggle even with minimal constraints, while stronger models can accommodate broader rule sets
5. **Not a replacement**: LLM-generated code with compliance prompts still requires CI-integrated static analysis and code review—prompts serve as guardrails, not certification artifacts

## Citation

If you use this dataset, the distilled prompts, or reference this work, please cite:

```bibtex
@article{woloszyn2025reducing,
  title={Cutting {MISRA C++:2023} violations in {LLM}-generated code by up to 83\% with prompt engineering},
  [TODO]
}
```

## License

This repository is licensed under the [Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0)](LICENSE).

**You are free to:**
- Share — copy and redistribute the material in any medium or format
- Adapt — remix, transform, and build upon the material

**Under the following terms:**
- Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made
- NonCommercial — You may not use the material for commercial purposes

See the [LICENSE](LICENSE) file for the complete license text.

## Copyright Notices

**MISRA Copyright Disclaimer:**

“MISRA”, “MISRA C”, and “MISRA C++” are registered trademarks of The MISRA Consortium Limited. Used here solely to reference guideline identifiers; no MISRA guideline text is reproduced.

## Acknowledgments

This research was conducted at Parasoft Corporation. Parasoft C/C++test was used for MISRA C++:2023 compliance verification.

Various LLMs were used in the preparation of the paper and experimental protocols, including OpenAI's o3, GPT-5, Claude Sonnet 4.0, 4.5, and Claude Opus 4.1 for tasks ranging from grammar corrections to code development and data analysis.

## Related Resources

- **Paper preprint**: [Link to be added upon publication]
- **MISRA C++:2023 Standard**: [https://misra.org.uk/](https://misra.org.uk/)
- **Parasoft C/C++test**: [https://www.parasoft.com/products/parasoft-c-ctest/](https://www.parasoft.com/products/parasoft-c-ctest/)
- **Aider AI pair programming**: [https://aider.chat/](https://aider.chat/)
- **Aider polyglot benchmark**: [https://aider.chat/docs/leaderboards/](https://aider.chat/docs/leaderboards/)
- **Modified benchmark framework**: [https://github.com/paraemsi/polyglot-benchmark](https://github.com/paraemsi/polyglot-benchmark)
- **Aider integration patch**: [https://gist.github.com/paraemsi/6ac59bf2d3583f3a16efaa0798e146fc](https://gist.github.com/paraemsi/6ac59bf2d3583f3a16efaa0798e146fc)
