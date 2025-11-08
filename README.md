# Mini-Shell

Mini-Shell is a simplified implementation of a Unix shell written in C as part of the 42 curriculum.  
It allows executing commands, managing environment variables, and reproduces some core features of `bash`.

---

## Technical details
- Language: C  
- Library: Unix system functions (`execve`, `fork`, `pipe`, etc.)  

---

## Features
- Execution of external commands (`ls`, `cat`, etc.)  
- Built-in commands:
  - `cd`
  - `echo`
  - `pwd`
  - `exit`
  - handling of `env`, `export`, `unset`  
- Environment variables management (`PWD`, `OLDPWD`, `PATH`)  
- Redirections and pipes (`>`, `<`, `|`)  
- Error handling with clear messages  

---

## Build and run
Compile with:

```bash
make
```
![giphy](https://github.com/user-attachments/assets/4f0190e4-9a1f-4fd1-a5bb-dce46eef8c9b)
