# Linux Process Management Scenarios

This project focuses on exploring process creation, termination, and resource usage in the Linux operating system using the C programming language. It consists of five scenarios, each designed to help you understand different concepts related to processes.

## Project Overview

### 1. The Prolific Parent
- The parent process spawns a random number of children (between 10 and 15).
- Each child introduces itself, waits for a short time, and then terminates with a specific exit code.

### 2. Lifespan Generation
- The parent process picks a random number for the number of lifespans to be explored (between 7 and 10).
- It then creates a child that decrements the lifespan count and, if non-zero, creates its own child.
- Processes wait until their child returns and exits with a value one greater than its child's exit value.

### 3. The Explorer
- The parent process moves around the file system randomly, changing the current working directory.
- It forks a child at each location, which runs the 'ls -alh' command. The child's listing output should match the selected directory.

### 4. The Slug
- This process randomly selects a wait time (between 1 and 5 seconds) and runs either 'last -d --full' or 'id -u'.
- The scenario is a single process program; no child processes are forked.

### 5. The Slug Race
- The parent process creates four children that run The Slug executable in parallel.
- The parent prints out updates on which children are still competing and reports the results when each child completes.

## Getting Started

### Prerequisites
- Make sure you have a C compiler installed on your system.
- The code is designed to run on a Linux system.

### Instructions
1. Clone the repository to your local machine.
2. Navigate to the project directory.

#### Build and Run Scenarios
3. Use the provided Makefile to compile each scenario separately:
    ```bash
    make prolific
    make generation
    make explorer
    make slug
    make slugrace
    ```

4. Run the compiled executables:
    ```bash
    ./prolific
    ./generation
    ./explorer
    ./slug [1, 2, 3, or 4]
    ./slugrace
    ```
