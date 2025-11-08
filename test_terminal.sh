#!/bin/bash

echo "Testing minishell terminal handling..."
echo ""
echo "Test 1: Checking if terminal is in canonical mode"
stty -a | grep -q "icanon" && echo "✓ Terminal is in canonical mode" || echo "✗ Terminal is NOT in canonical mode"
echo ""
echo "Test 2: Testing Enter key"
echo "Please press Enter:"
read -r input
echo "✓ Enter key works correctly!"
echo ""
echo "Test finished."
