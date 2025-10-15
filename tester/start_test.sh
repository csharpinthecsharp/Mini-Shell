#!/bin/bash

cd minishell_tester || exit

./tester builtins

echo
read -p "Enter to continue [Syntax Test]"

./tester syntax

echo
read -p "Enter to continue [Pipes Test]"
./tester pipes
