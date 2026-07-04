# pipex

A 42 School project that recreates a simple Unix pipeline in C.

The program executes two commands and connects them with a pipe, reproducing the behavior of:

```bash
< infile cmd1 | cmd2 > outfile
```

The goal of the project is to understand how Unix processes communicate through file descriptors, pipes, forks, and command execution.

---

## What this project shows

* Process creation with `fork`
* Inter-process communication with `pipe`
* File descriptor management with `dup2`
* Command execution with `execve`
* Input/output redirection
* PATH resolution for shell commands
* Error handling for files, commands, and child processes
* Memory management in C
* Modular C project structure
* Makefile-based build workflow

---

## Tech stack

* C
* Unix system calls
* Makefile
* Libft

---

## How it works

`pipex` receives an input file, two commands, and an output file:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

It behaves like this shell command:

```bash
< infile cmd1 | cmd2 > outfile
```

Example:

```bash
./pipex infile "grep hello" "wc -l" outfile
```

Equivalent shell behavior:

```bash
< infile grep hello | wc -l > outfile
```

---

## Usage

Clone the repository:

```bash
git clone git@github.com:carolinapapes/42_pipex.git
cd 42_pipex
```

Build the project:

```bash
make
```

Run the program:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example:

```bash
echo "hello world" > infile
./pipex infile "cat" "wc -w" outfile
cat outfile
```

Clean object files:

```bash
make clean
```

Remove object files and the binary:

```bash
make fclean
```

Rebuild from scratch:

```bash
make re
```

---

## Project structure

```text
.
├── include/        # Header files and type definitions
├── libs/libft/     # Custom C utility library
├── src/            # Pipex source files
├── Makefile        # Build rules
└── subject.pdf     # 42 project subject
```

---

## Main concepts practiced

### Processes

The project uses child processes to execute commands independently, similar to how a shell runs commands in a pipeline.

### Pipes

A pipe connects the output of the first command to the input of the second command.

### File descriptors

The program redirects standard input and standard output using file descriptors, allowing commands to read from files, write to files, and communicate through the pipe.

### Command execution

Commands are resolved through the environment `PATH` and executed with `execve`.

### Error handling

The project handles common failure cases such as invalid arguments, inaccessible files, command resolution errors, failed forks, failed pipes, and failed executions.

---

## Why this project matters

Although `pipex` is a small system programming project, it builds important foundations for backend and full-stack development:

* Understanding how processes run
* Understanding how shells execute commands
* Managing low-level resources safely
* Thinking carefully about errors and edge cases
* Building modular and maintainable C code
* Working close to the operating system

These concepts are useful beyond C, especially when working with servers, CLIs, Docker, process management, streams, and backend infrastructure.

