# Simple shell
Welcome to the repository of our simple shell implementation in C! This project emulates basic functionality of the Unix shell.

## Requirements

### General

- **Editors allowed**: `vi`, `vim`, `emacs`
- **Compilation**:
  - All files will be compiled on Ubuntu 20.04 LTS.
  - Compilation command: `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
- All files should end with a newline.
- A `README.md` file is mandatory at the root of the project directory.
- Coding style:
  - Code should follow the `Betty` style.
  - It will be checked using `betty-style.pl` and `betty-doc.pl`.
- The shell should be free of memory leaks.
- No more than 5 functions per file.
- All header files should be include guarded.
- System calls should be used judiciously.

### Repository

- One project repository per group.
- Collaborators should be added to avoid having repositories with the same name.
- There should be an `AUTHORS` file at the root of your repository.

### Output

Your shell must match the output of `sh` (`/bin/sh`), as well as error outputs. The only difference should be the name of the program.

**Example with `/bin/sh`**:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
```

**Example with our shell (`hsh`)**:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
```

### Allowed Functions & System Calls

- `access`
- `chdir`
- `close`
- `closedir`
- `execve`
- `exit`
- `_exit`
- `fflush`
- `fork`
- `free`
- `getcwd`
- `getline`
- `getpid`
- `isatty`
- `kill`
- `malloc`
- `open`
- `opendir`
- `perror`
- `read`
- `readdir`
- `signal`
- `stat (__xstat)`
- `lstat (__lxstat)`
- `fstat (__fxstat)`
- `strtok`
- `wait`
- `waitpid`
- `wait3`
- `wait4`
- `write`

For a detailed description and usage of these functions, use `man` (e.g., `man 2 access`).

## Usage

To start the shell in **interactive mode**:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

For **non-interactive mode**:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
```

## Testing

Further testing procedures and the checker will be released towards the end of the project timeline.

---
