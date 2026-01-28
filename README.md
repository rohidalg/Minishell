*This project was created as part of the 42 curriculum by rohidalg, wiljimen.*

# Minishell

## Description

Minishell is a simplified implementation of a Unix shell, developed in C as part of the 42 School curriculum.
The objective of this project is to understand how a shell works internally by recreating its core behavior from scratch.

The program is capable of parsing and executing commands, managing environment variables, handling pipes and redirections, and implementing several built-in commands. Special attention is given to process management, file descriptors, signals, and memory safety.

---

## Features

- Execution of commands using absolute or relative paths.
- Environment variable expansion (`$VAR`, `$?`)
- Built-in commands:
  - `echo`.
  - `cd`.
  - `pwd`.
  - `export`.
  - `unset`.
  - `env`.
  - `exit`.
- Pipes (`|`).
- Redirections:
  - Input (`<`).
  - Output (`>`).
  - Append (`>>`).
  - Heredoc (`<<`).
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).
- Proper error handling and exit status management.
- Memory leak free (tested with Valgrind / AddressSanitizer).

---

## Instructions

To initiate this project, after compiling with *make*, we are going to write "./minishell" in our terminal,
and we can start using it.

### Requirements

- Linux or macOS.
- `cc`.
- `make`.
- GNU Readline library.

### Compilation

Clone the repository and compile the project using:

*make*

*To remove object files* -> make clean
*To remove object files and executable* -> make fclean
*To recompile* -> make re

### Resources

Bash manual: https://www.gnu.org/software/bash/manual/

Video from YouTube: https://www.youtube.com/watch?v=yTR00r8vBH8

Linux man pages (man bash, man fork, man execve, man pipe, man dup2)

### Use of AI

Artificial Intelligence tools (such as ChatGPT and Gemini) were used as a learning and support resource, mainly for:

- Understanding shell behavior and edge cases.

- Clarifying system calls and Unix concepts.

- Reviewing logic and detecting potential memory issues.


