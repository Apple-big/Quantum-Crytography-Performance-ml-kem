# Post-Quantum Cryptography for Financial Transaction Systems

## Performance Analysis and Implementation of the ML-KEM (CRYSTALS-Kyber) Algorithm

## Project Overview

Quantum computing threatens the long-term security of classical public-key cryptographic
algorithms such as RSA and Elliptic Curve Cryptography (ECC), both of which are widely
used to secure financial systems. To address this challenge, the National Institute of
Standards and Technology (NIST) standardized the Module-Lattice-Based Key
Encapsulation Mechanism (ML-KEM) in FIPS 203 as the primary quantum-resistant key
establishment algorithm.
This project presents a comparative benchmarking evaluation of the three standardized
ML-KEM parameter sets:

- ML-KEM-512
- ML-KEM-768
- ML-KEM-1024

The evaluation was performed using a controlled benchmarking framework that simulates
repeated key establishment operations representative of future financial transaction
systems.
---

> **This repository contains the implementation, benchmarking framework, experimental results, and supporting documentation developed for my MSc Data Science and Big Data Analytics with Advanced Practice dissertation at Wrexham University, August 2026**

---

## Research Objectives

The study evaluates and compares the three standardized ML-KEM parameter sets using
the following performance metrics:

- Key generation latency
- Encapsulation latency
- Decapsulation latency
- Total key establishment latency
- Transaction throughput
- Public key size
- Secret key size
- Ciphertext size
The study also examines the computational trade-offs associated with increasing security
levels and identifies the most suitable parameter set for future financial transaction systems.

---

## Validation
Before benchmarking, the implementation was verified through:
- Functional correctness testing
- NIST Automated Cryptographic Validation Protocol (ACVP) Known Answer Tests
(KATs)
These validation procedures ensured that all benchmark measurements were obtained from
a standards-compliant implementation of ML-KEM.

---

## Experimental Configuration
Each standardized parameter set was benchmarked using four workloads:

- 10,000
- 50,000
- 500,000
- 1,000,000

Each workload was executed five independent times, after which the mean and standard
deviation were calculated.
Each benchmark iteration performed:

- Key generation
- Encapsulation
- Decapsulation
- Shared secret verification
- Timing measurement
- Key size measurement

---

## Key Findings

The experimental evaluation demonstrated that:
- ML-KEM-512 consistently achieved the lowest latency and highest throughput.
- ML-KEM-768 provided the best overall balance between computational efficiency
and quantum-resistant security.
- ML-KEM-1024 provided the highest security level but incurred the greatest
computational overhead.
- Public key, secret key and ciphertext sizes remained constant across all benchmark
workloads, confirming that communication overhead depends only on the selected
parameter set rather than transaction volume.
- The implementation maintained stable performance across increasing workloads,
with only a small number of isolated benchmark outliers attributable to system-level
execution variability.

---

## Repository Structure

```text
.
├── experiments/
│   ├── research_experiments.cpp 
│  
│
├── results/
│   ├── benchmark_10000.csv
│   ├── benchmark_50000.csv
│   ├── benchmark_500000.csv
│   └── benchmark_1000000.csv
│
├── README.md
└── CMakeLists.txt
```

---

## Experimental Setup

### Hardware

- Apple MacBook Pro
- Apple M4 SoC
- ARM64 Architecture
- 10-Core CPU
- 24 GB Unified Memory
- macOS

### Software

- C++20
- Apple Clang Compiler
- CMake
- Release Build
- Compiler Optimisation: 

The implementation was benchmarked using native execution with  

---

## Benchmark Configuration

Each ML-KEM parameter set was evaluated using four benchmark sizes:

| Iterations |
|------------|
| 10,000 |
| 50,000 |
| 500,000 |
| 1,000,000 |

Each benchmark performs:

1. Key Generation
2. Encapsulation
3. Decapsulation
4. Shared Secret Verification
5. Timing Collection

Performance metrics include:

- Key Generation Latency
- Encapsulation Latency
- Decapsulation Latency
- Total Latency
- Throughput (Transactions per Second) 
---

## Reproducing the Results

Clone the reference implementation:

```bash
git clone https://github.com/itzmeanjan/ml-kem.git
cd ml-kem
```

Create a Release build:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

Run the validation tests before benchmarking.

Execute benchmarks for each parameter set using:

- ML-KEM-512
- ML-KEM-768
- ML-KEM-1024

with iteration counts of:

- 10,000
- 50,000
- 500,000
- 1,000,000

Export benchmark results to CSV for analysis. 
---

## Research Contribution

TThis repository provides a reproducible benchmarking framework for evaluating standardized
ML-KEM parameter sets under controlled experimental conditions.
The work contributes:
- A reproducible benchmarking methodology
- Functional validation and standards-compliant verification of ML-KEM
- Comparative performance measurements across all standardized parameter sets

- Experimental evidence supporting parameter selection for future financial transaction
systems
- Publicly available benchmark source code and datasets to facilitate reproducibility
and further research

---

## Technologies Used

- C++20
- ML-KEM (FIPS 203)
- CMake
- Apple Clang
- CSV Data Analysis
- High-resolution Performance Benchmarking

---

## Reference Implementation

This project builds upon the excellent open-source implementation maintained by:

https://github.com/itzmeanjan/ml-kem

All modifications, benchmarking code, experimental design, and analysis presented in this repository were developed as part of the MSc dissertation.

---

## Acknowledgements

This work builds upon the open-source ML-KEM implementation developed by Anjan Roy and follows the NIST FIPS 203 specification for the Module-Lattice-Based Key Encapsulation Mechanism (ML-KEM). The original implementation provided the cryptographic foundation upon which the benchmarking framework and experimental evaluation presented in this dissertation were developed.
