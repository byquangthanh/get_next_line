# Get Next Line (GNL)

## Introduction

The `get_next_line` function is a project that is focused on static variables, file descriptors, and how to parse text data. The goal of this function is to read content from a file descriptor, line by line, until the end of the file.

## Project Objective

The main objective of this project is to create a function that returns a line read from a file descriptor. The function should be memory leak-free and optimized for speed and efficiency.

## Features

- Handles reading from file descriptors line by line.
- Efficient memory management to prevent leaks.

## How to Use

### Requirements

- A C compiler (I used cc)
- Make (optional for compilation automation)

### Compilation

To compile the `get_next_line` library, run the following command:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o get_next_line
```

Note: Adjust `BUFFER_SIZE` according to your needs. It determines how much of the file is read at each call of `read()`.

### Integration

To use `get_next_line` in your project:

1. Include the header file in your source:

```c
#include "get_next_line.h"
```

2. Compile your project along with `get_next_line.c` and `get_next_line_utils.c`.

3. Use the `get_next_line` function to read lines from a file descriptor:

```c
int fd = open("your_file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL) {
    printf("%s", line);
    free(line);
}
close(fd);
```

## Contribution

Contributions to improve `get_next_line` are welcome. Please follow the standard GitHub pull request process to submit your enhancements.
