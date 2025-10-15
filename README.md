# 🐚 Mini-Bash

Mini-Bash is a small Unix shell inspired by **bash**, built as part of the 42 curriculum.  
It handles command parsing, execution, pipes, redirections, environment variables, and builtins.

---

## ✨ Features

- Prompt with command history  
- Executable search via `$PATH`, relative or absolute path  
- Quotes handling: `'...'` and `"..."`  
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)  
- Pipes `|`  
- Environment variables `$VAR` and `$?`  
- Signal handling:  
  - `Ctrl-C` → new prompt  
  - `Ctrl-D` → exit  
  - `Ctrl-\` → ignored  
- Builtins:  
  - `echo -n`  
  - `cd`  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`

---

## 🛠️ Build

```bash
make
./mini-bash
