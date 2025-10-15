#!/bin/bash

cd minishell_tester || exit

echo
read -p "Press enter to start the test [ENTER]"
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
