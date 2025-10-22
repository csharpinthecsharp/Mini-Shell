#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${CYAN}Cloning minishell tester repository...${NC}"
git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester || exit

echo -e "${CYAN}"
echo " _"
echo "( \\"
echo " \\ \\"
echo " / /                |\\\\"
echo "/ /     .-'''''-.   / ^\`-."
echo "\\ \\    /         \\_/  {|} \`o"
echo " \\ \\  /   .---.   \\\\ _  ,--'"
echo "  \\ \\/   /     \\,  \\( \`^^^"
echo "   \\   \\/\\      (\\  )"
echo "    \\   ) \\     ) \\ \\"
echo "jgs  ) /__ \\__  ) (\\ \\___"
echo "    (___)))__))(__))(__))"
echo -e "${NC}"
echo
read -p "$(echo -e ${YELLOW}Type [Y] to start, Type [N] to leave:${NC} ) " answer
echo

if [[ "$answer" == "N" || "$answer" == "n" ]]; then
    echo -e "${RED}Exiting...${NC}"
    cd ..
    rm -rf minishell_tester
    exit
elif [[ "$answer" == "Y" || "$answer" == "y" ]]; then
    echo -e "${GREEN}Running full checks...${NC}"
    ./tester
else
    echo -e "${RED}Invalid input. Please type Y or N.${NC}"
fi

cd ..
rm -rf minishell_tester