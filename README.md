# c_hash_table
**A basic hash table implementation in C**

## What it does
This project provides a simple hash table implementation in C with support for both chaining and open addressing collision resolution. It's a small, single-purpose tool designed for educational purposes.

## Install
To use this project, you'll need a C compiler like GCC. You can install it on Ubuntu or Debian with:
```bash
sudo apt-get update && sudo apt-get install build-essential
```
On macOS with Homebrew, you can install it with:
```bash
brew install gcc
```
To install the project, clone this repository and run:
```bash
make install
```
This will compile the project and install it in your system's `bin` directory.

## Usage
To use the hash table, you can simply run the `ht` command followed by the desired operation. For example:
```bash
ht insert 5
ht search 5
ht delete 5
```
You can also specify the collision resolution method by using the `-c` flag:
```bash
ht -c chaining insert 5
ht -c open addressing search 5
```
## Build from source
To build the project from source, simply run:
```bash
make
```
This will compile the project using GCC.

## Run tests
There are no tests for this project. It's a simple implementation designed for educational purposes.

## Project structure
The project has the following files:
* `hash_table.c`: The main implementation of the hash table.
* `ht.c`: A simple command-line interface for interacting with the hash table.
* `Makefile`: A Makefile for building and installing the project.

## License
Copyright (c) 2026 SamyAlderson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.