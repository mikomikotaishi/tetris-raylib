CXX = g++
SELF_DIR := $(shell pwd)
DIRECTORIES = include src src/game src/grid src/piece src/utility
INC = $(addprefix -I$(SELF_DIR)/,$(DIRECTORIES)) -I$(SELF_DIR)/.
SOURCES = $(wildcard $(addsuffix /*.cpp,$(DIRECTORIES))) $(wildcard *.cpp)  # List of all .cpp files

# Final release flags
# CXXFLAGS = -fsanitize=address -I/usr/include -Wall -g -MMD -O2 -Werror=vla -Werror=vla ${INC} # Compilation flags
# LDFLAGS = -fsanitize=address -lraylib -lm -lpthread -ldl -lrt -lX11 # Linking flags

# Debug flags
CXXFLAGS = -DDEBUG -fsanitize=address -I/usr/include -Wall -g -MMD -O2 -Werror=vla -Werror=vla ${INC} # Compilation flags
LDFLAGS = -fsanitize=address -lraylib -lm -lpthread -ldl -lrt -lX11 # Linking flags

BUILD_DIR = bin
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, ${SOURCES})  # .o files in the bin directory
DEPENDS = $(OBJECTS:.o=.d)   # .d files in the bin directory
EXEC = tetris

# ANSI color codes
GREEN := $(shell echo -e "\033[32m")
RESET := $(shell echo -e "\033[0m")

# Progress bar variables
TOTAL_FILES := $(words $(SOURCES))
CURRENT_FILE = 0
BAR_LENGTH = 50

# Store start time in nanoseconds
START_TIME := $(shell date +%s.%N)

# Function to calculate elapsed time in seconds and milliseconds
define calc_elapsed
$(shell echo "$(shell date +%s.%N) - $(START_TIME)" | bc)
endef

# Function to format time with milliseconds
define format_time
$(shell echo "$1" | awk '{mins=int($$1/60); secs=int($$1%60); ms=int(($$1*1000)%1000); printf "%02d:%02d.%03d", mins, secs, ms}')
endef

# Function to draw progress bar and compilation status
define draw_progress_bar
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PROGRESS=$(shell echo "scale=2; $(CURRENT_FILE) * 100 / $(TOTAL_FILES)" | bc))
	$(eval FILLED=$(shell echo "scale=0; $(PROGRESS) * $(BAR_LENGTH) / 100" | bc))
	$(eval EMPTY=$(shell echo "$(BAR_LENGTH) - $(FILLED)" | bc))
	$(eval ELAPSED=$(call calc_elapsed))
	$(eval TIME_STR=$(call format_time,$(ELAPSED)))
	@echo '$(GREEN)Compiling$(RESET) $<'
	@if [ $(CURRENT_FILE) -lt $(TOTAL_FILES) ]; then \
		printf '[%-*s%*s] %3.1f%% (%d/%d files) $(BOLD)[%s]$(RESET)\n' \
			'$(FILLED)' \
			'$(shell printf '%*s' '$(FILLED)' | tr " " "#")' \
			'$(EMPTY)' \
			'' \
			'$(PROGRESS)' \
			'$(CURRENT_FILE)' \
			'$(TOTAL_FILES)' \
			'$(TIME_STR)'; \
	else \
		printf '[%*s] 100.0%% (%d/%d files) $(BOLD)[%s]$(RESET)\n' \
			'$(BAR_LENGTH)' \
			'$(shell printf '%*s' '$(BAR_LENGTH)' | tr " " "#")' \
			'$(TOTAL_FILES)' \
			'$(TOTAL_FILES)' \
			'$(TIME_STR)'; \
	fi
endef

# Create the build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Create the necessary subdirectories
$(shell mkdir -p $(BUILD_DIR)/src)

# Target to build the executable
${EXEC}: ${OBJECTS}
	@echo -e "\n$(GREEN)Linking$(RESET) executable..."
	@${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} $(LDFLAGS)
	@echo -e "\n $(GREEN)Build complete:$(RESET) ${EXEC} $(BOLD)[Total time: $(call format_time,$(call calc_elapsed))]$(RESET)"

# Rule to build object files from source
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(call draw_progress_bar)
	@${CXX} ${CXXFLAGS} -c $< -o $@

# Include dependency files
-include $(DEPENDS)

.PHONY: clean

# Clean the build directory and executable
clean:
	@echo "$(GREEN)Cleaning$(RESET) build files..."
	@rm -rf $(BUILD_DIR) ${EXEC}
	@echo "Clean complete"
