# 🧠 Heap Memory Allocator Simulator

A custom memory allocator implementation in C that simulates dynamic memory management with `malloc` and `free` functionality in a controlled heap environment.

## 📊 Overview

This project implements a complete memory management system that mimics the behavior of standard library functions `malloc()` and `free()`. It provides a hands-on understanding of how operating systems manage dynamic memory allocation, fragmentation, and block coalescing.

## 🎯 Features

- **Custom Allocation**: Implements `my_malloc()` for memory allocation
- **Memory Deallocation**: Implements `my_free()` for releasing memory
- **Block Splitting**: Efficiently splits large blocks to minimize waste
- **Coalescing**: Automatically merges adjacent free blocks to reduce fragmentation
- **Heap Visualization**: Real-time display of heap state and block layout
- **Fixed Heap Size**: Operates within a predefined 1024-byte heap space

## 🏗️ Architecture

### Data Structure
```c
typedef struct Block {
    size_t size;       // Block size in bytes
    int free;          // 1 = free, 0 = allocated
    struct Block *next; // Pointer to next block
} Block;
```

### Memory Layout
```
+-----------------------------------------------+
| Block Header | User Data | Block Header | ... |
| (size, free, | (allocated| (size, free, |     |
|  next)       |  memory)  |  next)       |     |
+-----------------------------------------------+
```

## 📂 Project Structure

```
heapmap/
├── main.c                 # Main source code with allocator implementation
├── bin/
│   └── Debug/
│       └── heapmap       # Compiled executable
├── obj/
│   └── Debug/
│       └── main.o        # Compiled object file
├── heapmap.cbp           # Code::Blocks project file
├── heapmap.depend        # Project dependencies
└── README.md            # This documentation
```

## 🚀 Getting Started

### Prerequisites
- GCC Compiler
- Make (optional)
- Code::Blocks (for IDE support)

### Compilation
```bash
# Using GCC directly
gcc -o heapmap main.c -Wall -Wextra

# Using Code::Blocks
# Open heapmap.cbp and build the project
```

### Running the Program
```bash
./bin/Debug/heapmap
```

## 📖 API Reference

### `void init_heap()`
Initializes the heap with a single free block of 1024 bytes.

### `void* my_malloc(size_t size)`
Allocates a block of memory of the requested size.

**Parameters:**
- `size`: Number of bytes to allocate

**Returns:**
- Pointer to allocated memory on success
- `NULL` if insufficient memory

### `void my_free(void* ptr)`
Releases previously allocated memory.

**Parameters:**
- `ptr`: Pointer to memory block to free

### `void print_heap()`
Displays the current state of the heap with block details.

## 🧪 Example Usage

```c
#include "heapmap.h"

int main() {
    init_heap();
    
    void *ptr1 = my_malloc(100);  // Allocate 100 bytes
    void *ptr2 = my_malloc(200);  // Allocate 200 bytes
    
    print_heap();  // View heap state
    
    my_free(ptr1);  // Free first allocation
    
    void *ptr3 = my_malloc(50);  // Allocate 50 bytes
    
    print_heap();  // View updated heap state
    
    return 0;
}
```

## 📊 Heap State Output Example

```
Initial heap:
Block at 0x55a5b3c6a260: size=1008, free=1, next=0x0
-------------------------

After allocating 100 bytes (p1):
Block at 0x55a5b3c6a260: size=100, free=0, next=0x55a5b3c6a2c8
Block at 0x55a5b3c6a2c8: size=900, free=1, next=0x0
-------------------------
```

## 🔍 How It Works

### Allocation Process (my_malloc)
1. Traverse the linked list of blocks
2. Find the first free block with sufficient size
3. If block is larger than needed, split it
4. Mark block as allocated
5. Return pointer to user data area

### Deallocation Process (my_free)
1. Mark block as free
2. Check if next block is also free
3. If yes, merge both blocks into one larger free block

### Block Splitting
When a free block is larger than requested:
- Creates a new block header after the allocated space
- Adjusts sizes accordingly
- Maintains linked list integrity

## 📈 Performance Considerations

- **First-Fit Allocation**: Simple but may cause fragmentation
- **Internal Fragmentation**: Wasted space within allocated blocks
- **External Fragmentation**: Free memory scattered in small chunks
- **Overhead**: Each block has 24 bytes of header (on 64-bit systems)

## 🧪 Testing Scenarios

The main program demonstrates:
1. Initial heap setup
2. Sequential allocations
3. Memory freeing
4. Re-allocation in freed space
5. Block splitting and coalescing

## 🐛 Known Limitations

- No alignment guarantees (unlike real `malloc`)
- Simple first-fit algorithm (not best-fit or worst-fit)
- No thread safety mechanisms
- Fixed heap size (1024 bytes)
- No error checking for pointer validity in `my_free`

## 🔧 Extending the Project

Potential improvements:
- Add best-fit/worst-fit allocation strategies
- Implement memory alignment (8/16-byte boundaries)
- Add thread safety with mutexes
- Create unit tests for edge cases
- Implement `calloc()` and `realloc()` equivalents
- Add heap corruption detection

## 📚 Learning Outcomes

This project helps understand:
- Dynamic memory management internals
- Memory fragmentation issues
- Data structure design for system programming
- Pointer arithmetic and memory manipulation
- Debugging memory-related issues

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## 📄 License

This project is open source and available for educational purposes.

## 👨‍💻 Author

**Bala Andegue**
- GitHub: [BalaAndegue](https://github.com/BalaAndegue)
- Project: [Heap Memory Allocator](https://github.com/BalaAndegue/heatmap)

---

**Note**: This is an educational implementation. For production use, always rely on your system's standard memory allocation functions.