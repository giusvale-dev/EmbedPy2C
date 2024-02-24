"""
hash_calculator.py

C Integration with Python Hash Calculator

Copyright © 2024 Giuseppe Valente<valentepeppe@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""
import hashlib

def calculate_hash(input_str, algorithm_flag):
    if algorithm_flag == 1:
        hash_result = hashlib.sha256(input_str.encode()).hexdigest()
    elif algorithm_flag == 2:
        # Using sha3-256 algorithm
        hash_result = hashlib.sha3_256(input_str.encode()).hexdigest()
    else:
        raise ValueError("Invalid algorithm flag. Supported values are 1 (SHA-256) and 2 (SHA3-256)")
    return hash_result

if __name__ == "__main__":
    # Example usage
    input_string = input("Enter a string to compute hash: ")
    algorithm_flag = int(input("Enter the algorithm flag (1 for SHA-256, 2 for SHA3-256): "))

    try:
        result = calculate_hash(input_string, algorithm_flag)
        print(f"Hash result: {result}")
    except ValueError as e:
        print(f"Error: {e}")