#makefile

MKDIR_P = mkdir -p
OUT_DIR = build/

# does this create a list?
.PHONY: directories
.PHONY: clean

all: directories main.o

main.o: src/main.c
	clang src/main.c -o build/main
	clang -c src/main.c -o build/main.o
	chmod +x build/main

directories:
	${MKDIR_P} ${OUT_DIR}

clean:
	rm -rf build
