#!/bin/bash

git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester || exit

echo
read -p "Type [Y] for each checks, Type [N] for full checks: " answer
echo

if [[ "$answer" == "Y" || "$answer" == "y" ]]; then
    echo "Running checks one by one..."
    ./tester builtins

    echo
    read -p "Enter to continue [Syntax Test]"
    ./tester syntax

    echo
    read -p "Enter to continue [Pipes Test]"
    ./tester pipes

    echo
    read -p "Enter to continue [Redirections Test]"
    ./tester redirects
elif [[ "$answer" == "N" || "$answer" == "n" ]]; then
    echo "Running full checks..."
    ./tester
else
    echo "Invalid input. Please type Y or N."
fi

cd ..
rm -rf minishell_tester
