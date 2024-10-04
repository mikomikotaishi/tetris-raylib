CXX = g++
SELF_DIR := $(shell pwd)
DIRECTORIES = include src src/game src/grid src/piece src/utility
INC = $(addprefix -I$(SELF_DIR)/,$(DIRECTORIES)) -I$(SELF_DIR)/.
SOURCES = $(wildcard $(addsuffix /*.cpp,$(DIRECTORIES))) $(wildcard *.cpp)  # List of all .cpp files
CXXFLAGS = -fsanitize=address -I/usr/include -Wall -g -MMD -O2 -Werror=vla -Werror=vla ${INC} # Compilation flags
# -fsanitize=address for debugging in CXXFLAGS and LDFLAGS
LDFLAGS = -fsanitize=address -lraylib -lm -lpthread -ldl -lrt -lX11 # Linking flags
BUILD_DIR = bin
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, ${SOURCES})  # .o files in the bin directory
DEPENDS = $(OBJECTS:.o=.d)   # .d files in the bin directory
EXEC = tetris

# Create the build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Create the necessary subdirectories
$(shell mkdir -p $(BUILD_DIR)/src)

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} $(LDFLAGS)

# Rule to build object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)  # Create the output directory for .o and .d files
	${CXX} ${CXXFLAGS} -c $< -o $@

# Include dependency files
-include $(DEPENDS)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) ${EXEC}
