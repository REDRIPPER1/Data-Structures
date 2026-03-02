# Project Title

A0- BST 

## Description

This project implements a pointer-based Binary Search Tree (BST) in C++ with support for Day–Stout–Warren (DSW) tree balancing.
The BST allows insertion of integer values, displays the tree structure, and applies the DSW algorithm to rebalance an unbalanced tree using rotations.

The DSW balancing process consists of:

* Phase 1: Converting the BST into a left-skewed vine using rotations

* Phase 2: Rebuilding the tree into a balanced form using repeated right rotations

* This implementation focuses on clarity and correctness rather than file-based input or advanced optimizations.

## Getting Started

### Dependencies

* Installing IDE for C++
* A C++ compiler

### Installing

* Download or clone the project from GitHub. 
* Ensure all project files are in the same folder

### Executing program

* Open a terminal in the project folder
* Compile using the Makefile:
```
make
```
* Run the program with an input command file:
```
./dsw file.txt
```

* The program will:
* Inserts a predefined set of integer values into the BST

* Displays the original (unbalanced) BST

* Applies DSW balancing

* Displays the balanced BST

* The tree is printed sideways to clearly visualize structure and balance.

## Help

If the program fails to run:

    Make sure all files are in the same folder.

    Make sure the terminal is in the project directory.

    Ensure the command file exists and is correctly formatted.

```

## Authors

Sulaksh Rajlawat
sulrr111@gmail.com

## Version History

* 0.1
    * Initial Release

## License

This project is licensed under the Sulaksh Rajlawat License - see the LICENSE.md file for details
