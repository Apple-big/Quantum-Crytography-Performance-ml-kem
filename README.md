# Post-Quantum Cryptography for Financial Transaction Systems

## Performance Analysis and Implementation of the ML-KEM (CRYSTALS-Kyber) Algorithm

This repository contains the implementation, benchmarking framework, experimental results, and supporting documentation developed for my MSc dissertation:

> **Post-Quantum Cryptography for Financial Transaction Systems: Performance Analysis and Implementation of the ML-KEM (CRYSTALS-Kyber) Algorithm** 

---

## Project Overview

Quantum computing presents a significant challenge to traditional public-key cryptography such as RSA and Elliptic Curve Cryptography (ECC). In response, the National Institute of Standards and Technology (NIST) standardized **ML-KEM (formerly CRYSTALS-Kyber)** as the recommended post-quantum Key Encapsulation Mechanism (FIPS 203).

This project experimentally evaluates the computational performance of the three standardized ML-KEM parameter sets:

- ML-KEM-512
- ML-KEM-768
- ML-KEM-1024

within a simulated financial transaction workflow to determine their suitability for high-performance financial systems. 

---

## Research Objectives

The study investigates:

- Key generation latency
- Encapsulation latency
- Decapsulation latency
- Total cryptographic latency
- Transaction throughput
- Security vs performance trade-offs
- Practical deployment considerations for financial transaction systems

---

## Key Findings

The benchmarking results demonstrate that:

- **ML-KEM-512** delivers the lowest latency and highest throughput.
- **ML-KEM-768** provides the best balance between computational efficiency and post-quantum security.
- **ML-KEM-1024** offers the highest security level with increased computational overhead.

Even the most computationally intensive parameter set completed a full key establishment operation in approximately **67 μs** while sustaining **over 14,000 transactions per second**, indicating that ML-KEM is practical for modern financial transaction systems.

---

## Repository Structure

```text
.
├── experiments/
│   ├── research_experiments.cpp
│   ├── throughput_analysis.cpp
│   ├── memory_analysis.cpp
│   ├── transaction_simulation.cpp
│   └── csv_export.cpp
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
- Compiler Optimisation: `-O3 -march=native`

The implementation was benchmarked using native execution with `std::chrono::high_resolution_clock`. 

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

This work contributes a reproducible benchmarking framework for evaluating standardized ML-KEM implementations under workloads representative of financial transaction systems.

The project provides:

- A reproducible experimental methodology
- Standards-compliant ML-KEM validation
- Comparative benchmarking of all three standardized parameter sets
- Performance analysis suitable for researchers and practitioners considering migration to post-quantum cryptography :

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

## Dissertation

**Elvis Chinaka**

**MSc Data Science and Big Data Analytics with Advanced Practice**

Wrexham University

2026

---

## Citation

If you use this repository in your research, please cite:

```text
Chinaka, E. (2026).

Post-Quantum Cryptography for Financial Transaction Systems:
Performance Analysis and Implementation of the ML-KEM (CRYSTALS-Kyber) Algorithm.

MSc Dissertation,
Wrexham University.
```

---


## Acknowledgements

```text
This work builds upon the open-source ML-KEM implementation developed by Anjan Roy and follows the NIST FIPS 203 specification for the Module-Lattice-Based Key Encapsulation Mechanism (ML-KEM). The original implementation provided the cryptographic foundation upon which the benchmarking framework and experimental evaluation presented in this dissertation were developed.
```