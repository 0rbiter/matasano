CC=clang
RM = rm -f 
MKDIR_P = mkdir -p
SRC_DIR = src/
INC_DIR = include/
BUILD_DIR = build/
CFLAGS=-v -O0 -fno-strict-aliasing -fno-omit-frame-pointer -g
ITEXTCAT = /usr/include/libexttextcat
INC=$(ITEXTCAT) $(INC_DIR)
INC_PARAMS=$(foreach d, $(INC), -I$d)
LDFLAGS=-lm

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
	    $(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	    $(CC) $(CFLAGS) $(INC_PARAMS) $< -c -o $@

clean:
	$(RM) $(BUILD_DIR)/*.o
	$(RM) $(BUILD_DIR)/$(EXECUTABLE)

run: all
	echo
	$(BUILD_DIR)/$(EXECUTABLE)
