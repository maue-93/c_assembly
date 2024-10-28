[C Assembly.pdf](https://github.com/user-attachments/files/17549140/C.Assembly.pdf)
# CPU ( run Assembly Code )

This project implements a basic stored-memory computer with a CPU and two memory regions: a stack and a code region. It is designed for the **CS203 Computer Organization** course, supporting a simulated **fetch-decode-execute cycle** using custom assembly language.

## Project Overview

This computer model simulates key CPU operations and memory handling. It includes a set of assembly instructions for arithmetic, data transfer, and control flow, as well as “dot-instructions” for debugging and observing CPU and memory states.

### Key Features

- **CPU with Registers**: Uses an accumulator (AC), program counter (PC), stack pointer (SP), and base pointer (BP), manipulated exclusively with bitwise operations.
- **Memory Regions**: Supports a stack and code memory, with structured memory locations.
- **Assembly Language Support**: Custom assembly instructions allow manipulation of CPU state, data transfer, and control flow.
- **Dot-Instructions**: Commands to display the current state of the CPU and specific memory regions for debugging.

## Instructions

### Running the Program

Execute the program from the command line as follows:

```bash
./simple_compute assembly_file.s
