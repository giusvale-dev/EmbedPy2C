/**
 * @file main.c
 * @brief C Integration with Python Hash Calculator
 * @author Giuseppe Valente <valentepeppe@gmail.com>
 * @date 2024-02-24
 * 
 * This C code demonstrates how to integrate the Python-based hash calculator
 * module into a C program. The provided Makefile simplifies the build process.
 * 
 * ## Overview
 * 
 * The C code includes a function named `sha_256` that interfaces with the Python script.
 * This function allows you to compute SHA-256 or SHA3-256 hashes for a given input string.
 * 
 * ## Note
 * 
 * This C code serves as a simple mock for integrating the Python-based hash calculator
 * functionality into C code. Ensure that you have the correct Python interpreter and library
 * paths configured for successful execution.
 * 
 * 
 * ## LICENSE
 * Copyright © 2024 Giuseppe Valente <valentepeppe@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include <string.h>

#define SHA256 	                  1
#define SHA3_256                  2
#define ERROR                     1
#define PYTHON_INITIALIZER_ERROR  2
#define PYTHON_MODULE_ERROR       3
#define PYTHON_FUNCTION_ERROR     4
#define OK                        0


/**
 * @brief Compute the sha_256 or sha3_256
 * 
 * @param str The input string
 * @param hash_code The result (hashcode)
 * @param type 1 = SHA256, 2 = SHA3-256
 * @return int 0 if success, a not zero value if fails
 */
static int sha_256(char * str, char * hash_code, int type) {

    int result = ERROR;

    if(str == NULL) {
        fprintf(stderr, "Input string cannot be NULL\n");
        goto normal_exit;
    }

    if(hash_code == NULL) {
        fprintf(stderr, "Input string cannot be NULL\n");
        goto normal_exit;
    }

    if(type != SHA256 && type != SHA3_256) {
        fprintf(stderr, "Input type not allowed\n");
        goto normal_exit;
    }
    
    // Initialize the Python interpreter
    Py_Initialize();
    if (Py_IsInitialized() == 0) { // 0 error, not 0 good!
        result = PYTHON_INITIALIZER_ERROR;
        goto exit;
    }

    // Append the script directory to the Python path
	const char *script_directory = "py_scripts";
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Insert(sys_path, 0, PyUnicode_DecodeFSDefault(script_directory));

    // Import the Python module
    PyObject *pModule = PyImport_ImportModule("hash_calculator");
    if (pModule == NULL) {
        PyErr_Print();  // Print error information
        result = PYTHON_MODULE_ERROR;
        goto exit;
    }

    // Get a reference to the Python function in the module
    PyObject *pFunction = PyObject_GetAttrString(pModule, "calculate_hash");
    // Check if the function was obtained successfully
    if (pFunction == NULL || PyCallable_Check(pFunction) == 0) {
        result = PYTHON_FUNCTION_ERROR;
        goto exit;
    }

    PyObject *pArgs = PyTuple_Pack(2, Py_BuildValue("s", str), Py_BuildValue("i", type));
    PyObject *pValue = PyObject_CallObject(pFunction, pArgs);

    if (pValue == NULL) {
        result = ERROR;
        goto exit;
    }

    //Data manipulation from python module!!
    char *hc = (char*) PyUnicode_AsUTF8(pValue);
    strcpy(hash_code, hc);
    result = OK;

    exit:
    // Release the reference to the module
    if(pModule != NULL) {
        Py_DECREF(pModule);
    }
    // Release the reference to the function
    if(pFunction != NULL) {    
        Py_XDECREF(pFunction);
    }
    // Release the reference to the result
    if(pValue != NULL) {
        Py_DECREF(pValue);
    }
    // Release the reference to the function arguments
    if(pArgs != NULL) {
        Py_DECREF(pArgs);
    }
    // Restore the Python path
    if(PyList_Size(sys_path) > 0) {
        PyList_SetSlice(sys_path, 0, 1, NULL);
        Py_Finalize();
    }
    normal_exit:
    return result;
}




int main() {

    int result = ERROR;
    char * toHash = "Hello World!";
    char * hash_code = (char*) malloc(sizeof(char) * 256);
    
    result = sha_256(toHash, hash_code, SHA256);
    if(result != OK) {
        goto exit;
    }
    printf("Plaintext = %s\t HashCode (SHA-256): %s\n", toHash, hash_code);

    //Hello World! hashed with SHA256
    char * expected = "7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d9069";
    if(strcmp(expected, hash_code) == 0) {
        printf("SHA-256 WORKS\n");
    }

    //Hello World! hashed with SHA3-256
    expected = "d0e47486bbf4c16acac26f8b653592973c1362909f90262877089f9c8a4536af";
    result = sha_256(toHash, hash_code, SHA3_256);
    if(result != OK) {
        goto exit;
    }
    printf("Plaintext = %s\t HashCode (SHA3-256): %s\n", toHash, hash_code);
    if(strcmp(expected, hash_code) == 0) {
        printf("SHA3-256 WORKS\n");
    }

    exit:
    free(hash_code);
    return result;
}
