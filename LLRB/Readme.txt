# Left-Leaning Red-Black Tree (LLRB Tree) Implementation

## Description

This project implements a Left-Leaning Red-Black Tree (LLRB Tree) in C++. An LLRB tree is a type of self-balancing binary search tree that maintains balance through coloring nodes red or black and ensuring left-leaning properties.

The implementation provides:
- Insertion of integer values with automatic balancing
- Visual tree printing showing node colors and structure
- Exception handling for invalid operations

**Note:** The remove/delete functionality is not yet implemented.

## Features

- **Insert Operation**: Adds integer keys to the tree while maintaining LLRB properties
- **Tree Visualization**: Prints the tree structure with color-coded nodes (red/black)
- **Automatic Balancing**: Uses rotations and color flips to maintain balance
- **Exception Handling**: Custom exception class for error management

## Getting Started

### Dependencies

- C++ compiler (g++ recommended)
- Make utility

### Building the Project

1. Ensure all source files are in the same directory:
   - `llrb.h`, `llrb.cpp`
   - `CustomErrorClass.h`, `CustomErrorClass.cpp`
   - `mainRB.cpp`
   - `Makefile`

2. Compile using the Makefile:
   ```
   make
   ```

### Running the Program

Execute the compiled program:
```
./main
```

The program will:
- Insert a series of integer values (10, 20, 30, 15, 25)
- Display the tree structure after each insertion
- Attempt to remove a value (currently not implemented)
- Show the final tree state

## Project Structure

- `llrb.h` / `llrb.cpp`: Main LLRB tree implementation
- `CustomErrorClass.h` / `CustomErrorClass.cpp`: Custom exception handling
- `mainRB.cpp`: Main program demonstrating tree operations
- `Makefile`: Build configuration

## Technical Details

The LLRB tree implementation includes:
- Node structure with data, color, and child pointers
- Left and right rotation operations
- Color flip operations
- Recursive insertion with balancing
- Tree traversal and printing with color visualization

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
