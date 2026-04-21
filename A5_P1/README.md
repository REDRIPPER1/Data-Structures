# Binomial Heap (Assignment)

## Overview

This repository implements a Binomial Heap in C++ for CSC-310 (Assignment 5). The key operations implemented and completed are:
- `insert(int)`
- `findMin()`
- `deleteMin()`
- `decreaseKey(int oldKey, int newKey)`
- `deleteKey(int key)`

Exception handling uses the provided `MyException` class (`CustomErrorClass.*`) for invalid operations and edge cases.

## Files
- `binomial.cpp`, `binomial.h` — heap implementation
- `main.cpp` — example usage / simple test runner
- `CustomErrorClass.h`, `CustomErrorClass.cpp` — exception class
- `Makefile` — build and `run` target

## Build & Run

Requirements: `g++`, `make`

Build and run:

```bash
make clean
make run
```

`make run` builds the `binomial` executable and runs the sample `main` (demonstrates inserts, `findMin`, `deleteMin`).

## Notes on Implementation
- `deleteMin()` locates the root with minimum key, removes it from the root list, reverses its children (detaching parents), and unions the resulting forest back into the heap.
- `decreaseKey(oldKey, newKey)` searches for a node with `oldKey`, validates `newKey <= current`, updates the key, and bubbles the node up by swapping keys with parents until heap order is restored.
- `deleteKey(key)` uses `decreaseKey(key, INT_MIN)` followed by `deleteMin()`.
- Errors (empty heap, key not found, invalid new key) throw `MyException` with descriptive messages.

## Answers to Questions (brief)

- ** How do binomial heaps improve the efficiency of merge operations compared
to binary heaps.**
  Binomial heaps merge in O(log n) by merging root lists by degree and consolidating trees while, Binary heaps have no efficient merge (merging two arrays then heapifying is O(n)).

- *Explain the time complexity of various operations in binomial heaps**
  - `insert`: O(1) amortized 
  - `findMin`: O(log n) 
  - `deleteMin`: O(log n)
  - `decreaseKey`: O(log n)
  - `deleteKey`: O(log n) 
  - `merge/union`: O(log n)

- **Why do we use the left-child right-sibling representation in binomial heaps
instead of traditional tree structures? How does it help with efficiency?**
   Two pointers child and sibling represents the arbitrary degree trees. It enables the efficient linking, iteration and child list reversal without arrays, meaning simplified memory use and tree manipulations that binomial operations need.
  

- **What is your opinion on this
https://ieeexplore.ieee.org/abstract/document/7275881**
It shows practical optimizations and heuristics for heap variants. We can read applied performance improvement of the syste. It has theoretical guesses on how standard binomial and fibonacci heap remain the baseline. So the paper's techniques are valuable when tuning for real world workloads.
