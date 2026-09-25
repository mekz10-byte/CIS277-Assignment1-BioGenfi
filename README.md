# CIS-277 Assignment 1: Network Packet Buffer Pool

## Student

Name: Mekhi Bio-Genfi

## Description

This project implements a fixed-size memory pool for storing network packet
data. The memory pool reserves a fixed amount of memory and divides it into
equally sized blocks.

Available blocks are managed using a custom Stack ADT. When allocate() is
called, a block is popped from the Stack. When deallocate() is called, the
block is pushed back onto the Stack so that its memory can be reused.

The program also demonstrates binary packet storage, memory reuse, pool
exhaustion, and protection against invalid or duplicate deallocations.

## Stack Implementation

I used a Dynamic Array to implement the Stack.

The Stack stores its elements in a dynamically allocated array. When the
array becomes full, a larger array is created and the existing elements are
copied into it. The Stack follows LIFO (Last In, First Out) behavior.

The memory pool uses Stack<void*> so that the Stack stores pointers to
available memory blocks.

## How to Compile

Compile the program using a C++17 compiler:

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp MemoryPool.cpp -o buffer_pool

## How to Run

Run the compiled program with:

./buffer_pool

## Analysis Questions

### 1. Why is a Stack appropriate for managing the free blocks in this memory pool?

A Stack provides a simple way to keep track of available memory blocks.
When a block is released, it is pushed onto the Stack. The next allocation
can pop that block from the top of the Stack and reuse it. This follows
LIFO (Last In, First Out) behavior.

### 2. What happens when the free-block Stack becomes empty?

When the Stack is empty, there are no free memory blocks available.
The allocate() function cannot provide another block, so it returns nullptr.

### 3. Why must a released block be returned to the Stack?

A released block must be returned to the Stack so the memory pool knows
that the block is available again. This allows a future call to allocate()
to reuse the block instead of requiring new memory.

### 4. What problem could occur if the same block were deallocated twice?

If the same block were deallocated twice, the same memory address could
appear in the free-block Stack more than once. The pool could then give the
same block to multiple allocations at the same time, which could cause data
corruption or other invalid memory behavior.

### 5. What is the Big-O time complexity of allocate()? Explain why.

allocate() is O(1). It checks whether the Stack is empty and then pops one
block from the top of the Stack. These operations take constant time and do
not depend on the number of blocks in the pool.

### 6. What is the Big-O time complexity of deallocate()? Explain why.

deallocate() is O(1). The program validates the pointer using arithmetic and
array lookups, updates the block's state, and pushes the pointer onto the
Stack. These operations take constant time and do not require searching
through all of the blocks.