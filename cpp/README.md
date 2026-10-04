# C++ Algorithms

This project includes three C++17 algorithms:

1. **Weighted course recommendation** — matches student interests to courses.
2. **Merge sort student ranking** — ranks students by academic average.
3. **Greedy enrollment allocation** — assigns limited seats to highest-scoring applicants.

Build with CMake:

```bash
cmake -S . -B build
cmake --build build
```

The programs are intentionally independent so they can be demonstrated in a thesis/capstone presentation or later exposed through a service layer.

For a production system, validate admission rules with the school's actual policies before using the allocation algorithm.
