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
https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExNGJhZWw4eHFjaXk5Mmlrcmd6ZzB5Mm84ZGp1dXhvcGQ3Z2lycWlzeiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Lopx9eUi34rbq/giphy.gif
