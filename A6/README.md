A6 — Gene Bank (CSC-310)

**Project**
- **Description:** C++ project for managing a simple gene bank. Demonstrates data storage, basic operations, and custom error handling for course assignment A6.

**Files**
- **Source:** [geneBank.cpp](geneBank.cpp), [customErrorHandling.cpp](customErrorHandling.cpp), [mainSamples.cpp](mainSamples.cpp)
- **Headers:** [geneBank.h](geneBank.h), [customErrorClass.h](customErrorClass.h), [Includes/customErrorClass.h](Includes/customErrorClass.h)
- **Extras:** [customErrorClass.cpp](customErrorClass.cpp), prebuilt [main](main), and [Makefile](Makefile)

**Build**
- **Requirements:** `g++`, `make`
- **Build:** Run `make` to compile the project (produces the `main` executable).
- **Clean:** Run `make clean` to remove build artifacts.

**Run / Usage**
- Build then run the executable produced by the Makefile:

```bash
make
./main
```

- For sample runs, inspect and run [mainSamples.cpp](mainSamples.cpp) or execute the provided `main` binary.

**Notes**
- Uses a custom error class for exception handling; see [customErrorClass.h](customErrorClass.h) and [customErrorHandling.cpp](customErrorHandling.cpp).
- Update or extend `geneBank.cpp`/`geneBank.h` for additional functionality.

**Author**
- Sulaksh Rajlawat