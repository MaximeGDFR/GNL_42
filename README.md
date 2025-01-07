# Get_next_line - 42 School Project

<div id="header" align="center">
  <img src="https://github.com/ayogun/42-project-badges/blob/main/badges/get_next_linem.png?raw=true" width="200"/>
</div>

<h2 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#usage">Usage</a>
</h2>

## About

The 42 school's __get_next_line__ project is where we learn to read from a __file descriptor__, as well as the use of __static variables__.

This function returns a single line from a given file descriptor. If called in a loop, get_next_line returns the entire contents of a file, __line by line until it reaches the end of the file__. It can be compiled specifying any buffer size.

## Usage
This function is not a stand-alone program, its files must be included and compiled within another project.

Example ``main.c``:
```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	fd = close(fd);
	return (0);
}
```
Compilation:
```bash
gcc main.c get_next_line.c get_next_line_utils.c
```
``BUFFER_SIZE`` can be specified at compilation to override the default ``BUFFER_SIZE``:
```bash
gcc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```
Execution:
```bash
./a.out [file]
```
Output should show the entire contents of the given file.

Execution with stdin:
```bash
./a.out /dev/tty
```
Program will wait for input, then once the enter key is pressed, print out the input as well as get_next_line's output. The process can be killed with ``ctrl-c``.
