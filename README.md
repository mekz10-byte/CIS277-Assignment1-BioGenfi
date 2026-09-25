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

A Stack makes it easy to store and reuse free blocks using LIFO. A released block is pushed back on top and can be reused by the next allocation.

### 2. What happens when the free-block Stack becomes empty?

There are no more blocks available, so allocate() returns nullptr.

### 3. Why must a released block be returned to the Stack?

It lets the memory pool know that the block is available to be used again.

### 4. What problem could occur if the same block were deallocated twice?

The same block could be added to the Stack twice and given to two different allocations, which could corrupt data.

### 5. What is the Big-O time complexity of allocate()? Explain why.

O(1), because it only checks the Stack and pops the top block.

### 6. What is the Big-O time complexity of deallocate()? Explain why.

O(1), because it validates the block and pushes it back onto the Stack without searching through all the blocks.
