# Hash Table Collision Handling Implementation

## Overview

This project implements and benchmarks six different hash table collision handling techniques in C++. The implementation uses an enum-based approach to switch between different collision resolution strategies and provides comprehensive performance analysis across three distinct datasets.

## Features

### Collision Handling Methods Implemented

1. **Chaining with Vectors** (`CHAINING_VECTOR`)
   - Uses `std::vector<std::pair<std::string, int>>` for each bucket
   - Simple and efficient for most operations

2. **Chaining with Lists** (`CHAINING_LIST`)
   - Uses `std::list<std::pair<std::string, int>>` for each bucket
   - Good for frequent insertions/deletions

3. **Chaining with AVL Trees** (`CHAINING_BST`)
   - Uses custom AVL tree implementation for each bucket
   - Provides O(log n) worst-case performance per bucket

4. **Linear Probing** (`LINEAR_PROBING`)
   - Open addressing with linear step size
   - Simple but can suffer from clustering

5. **Quadratic Probing** (`QUADRATIC_PROBING`)
   - Open addressing with quadratic step size (i²)
   - Reduces clustering compared to linear probing

6. **Double Hashing** (`DOUBLE_HASHING`)
   - Open addressing using two hash functions
   - Provides good distribution and reduces clustering

### Key Features

- **Dynamic Resizing**: Automatic table expansion when load factor exceeds thresholds
- **Comprehensive Benchmarking**: Performance comparison across insertion, search, and deletion operations
- **Statistics Reporting**: Load factor, empty buckets, and maximum chain length analysis
- **Multiple Datasets**: Three test datasets with varying collision characteristics
- **Standard Library Comparison**: Benchmarks against `std::unordered_map`

## Project Structure

```
Hash/
├── hash.h                 # Hash table class definition and enums
├── hash.cpp              # Hash table implementation
├── mainHash.cpp          # Main benchmarking program
├── CustomErrorClass.h    # Custom exception handling
├── CustomErrorClass.cpp  # Exception implementation
├── AVL/                  # AVL tree implementation directory
│   ├── avl.h
│   └── avl.cpp
├── data/                 # Test datasets
│   ├── no_collision_data.txt
│   ├── low_collision_data.txt
│   └── high_collision_data.txt
├── Makefile             # Build configuration
└── README.md            # This file
```

## Datasets

The project includes three datasets designed to test different collision scenarios:

- **`no_collision_data.txt`**: Randomly generated keys with minimal collisions
- **`low_collision_data.txt`**: Keys with moderate collision patterns
- **`high_collision_data.txt`**: Keys designed to produce high collision rates

Each dataset contains 100,000 key-value pairs in the format: `key value`

## Building and Running

### Prerequisites

- C++ compiler with C++11 support (g++ recommended)
- Make utility

### Compilation

```bash
make clean
make
```

### Execution

```bash
./main
```

The program will automatically run benchmarks for all collision handling methods across all three datasets and compare performance with `std::unordered_map`.

### Dataset Inspection

To examine the structure and content of the test datasets:

```bash
make inspector
./dataset_inspector
```

This will display detailed information about each dataset including sample records, key characteristics, and statistical analysis.

### Benchmark Table Generation

To generate formatted benchmark comparison tables:

```bash
make table
./benchmark_table
```

This creates clean, organized tables comparing all collision handling methods across all datasets with timing and statistical data.

## Implementation Details

### Hash Functions

- **Primary Hash** (`hash1`): Uses polynomial rolling hash with multiplier 31
- **Secondary Hash** (`hash2`): Uses djb2 algorithm, returns values in range [1, tableSize-1]

### Dynamic Resizing

- **Load Factor Thresholds**:
  - Chaining methods: 0.75
  - Probing methods: 0.65 (more conservative)
- **Resize Strategy**: Double the table size and rehash all elements

### Performance Characteristics

| Method | Insert | Search | Delete | Memory Usage |
|--------|--------|--------|--------|--------------|
| Chaining (Vector) | O(1) avg | O(1) avg | O(1) avg | Moderate |
| Chaining (List) | O(1) avg | O(1) avg | O(1) avg | Moderate |
| Chaining (AVL) | O(log n) | O(log n) | O(log n) | High |
| Linear Probing | O(1) avg | O(1) avg | O(1) avg | Low |
| Quadratic Probing | O(1) avg | O(1) avg | O(1) avg | Low |
| Double Hashing | O(1) avg | O(1) avg | O(1) avg | Low |

## Sample Output

```
========================================
Benchmarking with data from: data/no_collision_data.txt
========================================

----------------------------------------
Running benchmark for method: 0
----------------------------------------
Insertion time: 232279 microseconds
Search time: 52786 microseconds
Deletion time: 0 microseconds

Statistics for method: 0
Total elements: 100000
Load factor: 0.499983
Empty buckets: 121289
Max chain length: 6
```

## Key Observations

Based on benchmark results:

1. **Chaining methods** generally perform well across all datasets
2. **AVL tree chaining** excels with high collision data due to logarithmic bucket performance
3. **Probing methods** can suffer performance degradation with high collision rates
4. **Linear probing** is fastest for insertion but vulnerable to clustering
5. **Double hashing** provides the best distribution for probing methods
6. **Dynamic resizing** is crucial for maintaining performance as tables grow

## Academic Context

This implementation demonstrates fundamental data structures concepts:

- Hash table collision resolution strategies
- Trade-offs between time and space complexity
- Importance of load factor management
- Comparison of custom vs. standard library implementations
- Performance analysis across different data distributions

## Future Enhancements

- Implement deletion for probing methods (currently marks as deleted)
- Add more hash functions and collision resolution strategies
- Implement concurrent/parallel hash table operations
- Add memory usage profiling
- Extend benchmarking to include more operations and metrics

## License

This project is developed for educational purposes as part of CSC-310 coursework.