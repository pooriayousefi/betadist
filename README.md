# BetaDist

[![Build Status](https://github.com/pooriayousefi/betadist/actions/workflows/ci.yml/badge.svg)](https://github.com/pooriayousefi/betadist/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

A modern C++20 library for generating Beta distribution random numbers with high-quality seeding mechanisms. BetaDist provides both manual and automatic seeding options with robust parameter validation and efficient gamma-based simulation.

## 🚀 Features

- **Beta Distribution**: High-quality Beta(α, β) random number generation
- **Flexible Seeding**: Manual and automatic seeding with entropy detection
- **Modern C++20**: Uses concepts, floating-point concepts, and perfect forwarding
- **Parameter Validation**: Compile-time and runtime parameter checking
- **Thread-Safe**: Safe concurrent usage with proper random number generation
- **Cross-Platform**: Works on Linux (g++), macOS (clang++), and Windows (MSVC)

## 🎯 Quick Start

```cpp
#include "betadist.hpp"
#include <iostream>

int main() {
    // Create Beta distribution with α=2.0, β=5.0
    auto beta_gen = β::simulator(2.0, 5.0);
    
    // Use automatic seeding
    auto rng = std::mt19937{automatic::seeder()};
    
    // Generate random numbers
    for (int i = 0; i < 10; ++i) {
        double value = beta_gen(rng);
        std::cout << "Beta(2.0, 5.0) = " << value << std::endl;
    }
    
    return 0;
}
```

## 📚 API Reference

### Beta Distribution (`β` namespace)

#### `β::simulator<T>(T α, T β)`
Creates a Beta distribution simulator with shape parameters α and β.

#### `β::parameter_assertion<T>(T α, T β)`
Validates Beta distribution parameters at runtime.

### Seeding Mechanisms

#### Manual Seeding (`manual` namespace)
Provides deterministic seeding for reproducible results.

#### Automatic Seeding (`automatic` namespace)  
Provides high-quality random seeding using hardware entropy when available.

## 🔬 Mathematical Background

The Beta distribution uses the relationship between Beta and Gamma distributions:
```
If X ~ Gamma(α,1) and Y ~ Gamma(β,1), then X/(X+Y) ~ Beta(α,β)
```

## 🏗️ Building from Source

```bash
# Clone repository
git clone https://github.com/pooriayousefi/betadist.git
cd betadist

# Build with CMake
cmake --preset=default
cmake --build build/default
```

## 📄 License

This project is licensed under the MIT License.

---

**Author**: [Pooria Yousefi](https://github.com/pooriayousefi)  
**Repository**: [https://github.com/pooriayousefi/betadist](https://github.com/pooriayousefi/betadist)

Requirements:

Activate -std=c++20

Install Greek language package on OS
