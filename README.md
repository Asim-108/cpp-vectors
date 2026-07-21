# Custom C++ Vector Implementation

A custom, header-only, template-based implementation of a dynamic array (`myVector`) in C++ designed to replicate the functionality of `std::vector` from scratch without importing `<vector>`. 

This project was built to practice key C++ principles:
*   **Generic Programming**: Utilizes C++ templates (`template <typename T>`) to support primitive data types, standard library types, and user-defined structures.
*   **Manual Memory Management**: Directly manages dynamic memory allocation and deallocation on the heap.
*   **The Rule of Five**: Implements custom constructors, destructors, copy constructors, copy assignment operators, move constructors, and move assignment operators to ensure resource safety.
*   **Const Correctness**: Implements dual-accessor overloads for secure read-write and read-only access.

---

## Features

### 1. Element Access
*   `operator[]` & `at()`: Access elements by index (with bounds checking on `at()`).
*   `front()` & `back()`: Retrieve references to the first and last elements.

### 2. Capacity & Sizing
*   `size()`: Returns the number of active elements.
*   `capacity()`: Returns the total allocated memory space.
*   `empty()`: Checks if the vector has zero elements.
*   `reserve(n)`: Pre-allocates heap space to prevent frequent reallocations.
*   `resize(n)`: Resizes the container to contain `n` elements.

### 3. Modifiers
*   `push_back(val)`: Appends an element to the end, doubling capacity when full.
*   `pop_back()`: Removes the last element.
*   `insert(index, val)`: Inserts an element at a specific index, shifting subsequent elements to the right.
*   `erase(index)`: Removes an element at a specific index, shifting subsequent elements to the left.
*   `clear()`: Empties the vector without releasing the allocated capacity.

---

## How to Run

1. Compile the code using any C++17 compliant compiler:
   ```bash
   g++ -std=c++17 vector.cpp -o program
   ```

2. Run the executable:
   ```bash
   ./program
   ```
