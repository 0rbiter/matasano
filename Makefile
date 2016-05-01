CC=clang
MKDIR_P = mkdir -p
SRC_DIR = src/
INC_DIR = include/
BUILD_DIR = build/
CFLAGS=-v -O0 -fno-strict-aliasing -fno-omit-frame-pointer -g 
#CFLAGS=-v -I$(INC_DIR) -O0 -fno-omit-frame-pointer -g 
#CFLAGS=-v -O0 -g 

.PHONY: directories
.PHONY: clean

directories:
	${MKDIR_P} ${BUILD_DIR}

SRC_DIR = src
BUILD_DIR = build

EXECUTABLE = main
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
all: dir $(BUILD_DIR)/$(EXECUTABLE)

dir:
	    mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	    $(CC) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	    $(CC) $(FLAGS) $< -c -o $@

clean:
	rm -f $(SRC_DIR)*.o
	rm -f $(BUILD_DIR)*.o
	rm -f $(BUILD_DIR)/$(EXECUTABLE)
	rm -rf build

run: all
	echo
	$(BUILD_DIR)/$(EXECUTABLE)
