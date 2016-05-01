clear && make clean && make all && valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --show-reachable=yes ./build/main
