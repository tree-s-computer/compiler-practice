# Practice for GCC

## 1. Introduction

This repository is for practicing GCC.

## 2. How to compile

### 1. Single file

```bash
gcc single.c
```

Will generate `a.out` file. `a.out` is the default name of output file. To run the file, type:

```bash
./a.out
```

Explore files

```bash
file a.out
```


### 2. Multiple files

```bash
gcc -c extern.c
gcc -c main.c
gcc -o main main.o extern.o
```

Will generate `main` file. To run the file, type:

```bash
./main
```

-o option is used to specify the output file name.
