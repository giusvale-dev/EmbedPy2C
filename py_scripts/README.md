# Hash Calculator

This module provides a simple hash calculator that supports SHA-256 and SHA3-256 algorithms.

## Usage

1. Run the `hash_calculator.py` module directly to calculate the hash for a given string.

    ```bash
    python hash_calculator.py
    ```

2. Use the `calculate_hash` function in your Python code.

    ```python
    from py_scripts.hash_calculator import calculate_hash

    input_string = "Hello World"
    algorithm_flag = 1  # 1 for SHA-256, 2 for SHA3-256
    result = calculate_hash(input_string, algorithm_flag)
    print(f"Hash result: {result}")
    ```

## Mock for C Integration

This script can serve as a simple mock for using the `calculate_hash` function directly in C code. You can integrate the hash calculation functionality into your C program by calling the Python function using appropriate bindings or interfacing techniques.

## Testing

To run the tests, execute the following command from the project root:

```bash
python -m unittest py_scripts.test.hash_calculator_test