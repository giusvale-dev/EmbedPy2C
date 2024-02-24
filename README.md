# C Integration with Python Hash Calculator

This C code demonstrates how to integrate the Python-based hash calculator module into a C program. The provided Makefile simplifies the build process.

## Overview

The C code includes a function named `sha_256` that interfaces with the Python script. This function allows you to compute SHA-256 or SHA3-256 hashes for a given input string.

## Prerequisites

Ensure that you have Python 3.x installed on your system. The Makefile assumes Python 3.11; adjust the flags accordingly for a different Python version.

## How to Use

1. Build the executable using the provided Makefile:

    ```bash
    make
    ```

2. Run the compiled C executable:

    ```bash
    ./build/application
    ```