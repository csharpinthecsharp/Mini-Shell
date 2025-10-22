#!/bin/bash

RED="\033[1;31m"
GREEN="\033[1;32m"
NC="\033[0m"

clear

echo -e "${GREEN}=== Running minishell under Valgrind ===${NC}"
echo "Options: leak-check=full, track-fds, trace-children, show-leak-kinds=all"
echo "Suppressions: readline.supp"
echo

[ "$1" != "--no-wait" ] && sleep 1

if [ ! -f readline.supp ]; then
    echo -e "${RED}Suppression file not found, creating readline.supp...${NC}"
    cat > readline.supp << 'EOF'
{
   readline_leak
   Memcheck:Leak
   ...
   fun:readline
}
{
   add_history_leak
   Memcheck:Leak
   ...
   fun:add_history
}
{
   libc_bin_leak
   Memcheck:Leak
   ...
   obj:/*/bin/*
   ...
}
EOF
    echo -e "${GREEN}Suppression file created.${NC}"
    echo
fi

valgrind \
  --leak-check=full \
  --track-fds=yes \
  --trace-children=yes \
  --show-leak-kinds=all \
  --suppressions=readline.supp \
  ./minishell "${@}" 2>&1

echo
echo -e "${GREEN}Valgrind run complete.${NC}"
