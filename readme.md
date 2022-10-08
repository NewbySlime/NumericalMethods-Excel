# NumericalMethods-Excel

This repository is a "Library" to generate output to excel files. For methods, it is a user-generated methods, so expect no pre-defined methods ready to use.

Personally, this will be useful for me to code Numerical Method stuffs for my class without the need to create another function in header and then calling it from main. Just create a method and then adding it at the same c++ file.

## Building

Using c++ and c compiler and using make to automate it. Just call make to build it.

```bash
make
```

Or, if you want to create an object for it (for flexibility), then call;
```bash
make library
```

## Usage
For usage, mainly depends on the user-generated methods. Except for first question, it will ask for the name of the file you want to create (with or without '.xlsx'). Then after it, you will be prompted based on the parameters of the user-generated methods.

On user-generated side, you can create a function of the method, and then adding it using ADD_METHOD. For reference, you can check **methods.cpp**.