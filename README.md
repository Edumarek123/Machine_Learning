<div align="center">

# Machine Learning — Regression & Simulation

**An experimental workflow connecting data, multivariable regression, and simulation.**

![Languages](https://img.shields.io/badge/languages-C%20%7C%20Python-3776AB)
![Topics](https://img.shields.io/badge/topics-regression%20%7C%20simulation-6f42c1)
![Status](https://img.shields.io/badge/status-in%20progress-orange)

</div>

## Overview

This repository contains an exploratory data-science project that uses prepared data to calculate a multivariable linear-regression model, with the intention of supporting an optimization-oriented simulation.

The project is organized as a workflow rather than a single standalone script: data, model training, simulation, supporting code, and graph outputs are kept in separate areas.

## Workflow

1. **Data** — store and prepare the input data.
2. **Model training** — calculate a multivariable regression model.
3. **Simulation** — use model output in the simulation workflow.
4. **Visualization** — generate graphs to inspect results.

## Repository structure

```text
.
├── dados/              # Input data
├── graficos/           # Graph outputs
├── simulador/          # Simulation components
├── treinar_modelo/     # Model-training components
├── rpglib/             # Supporting library
├── main.cpp            # Main C entry point (as named in repository)
├── Model Diagram.pdf   # Model diagram
├── Regras.txt          # Project notes / rules
└── run_all.bat         # Workflow helper
```

## Technologies and methods

- C
- Python
- Multivariable linear regression
- Data-driven simulation
- Graph-based result inspection

## Running the project

The repository includes a Windows batch helper named `run_all.bat`. Review its commands and required paths before execution:

```bat
run_all.bat
```

The project contains multiple components, so dependencies and execution order should be confirmed from the scripts in each folder.

## Development status

The original development notes describe the project as ongoing and not yet optimized. They also identify memory-leak checking and broader validation as outstanding work.

For that reason, this repository should be treated as an experimental study, not as a validated optimization engine.

## Potential next steps

- Document the dataset schema and preprocessing
- Record model inputs, outputs, and evaluation metrics
- Add reproducible experiment configurations
- Validate memory usage and numerical behavior

## License

No license file was identified in the repository at the time of writing. Contact the author before redistributing or reusing the project.
