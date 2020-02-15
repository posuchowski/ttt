EXE = ttt
OBJS = main.o Board.o Memory.o AiPlayer.o BigBoard.o

TEST = test
TESTS = test.o
TEST_OBJS = Memory.o

CXX = g++
LD  = g++
OBJS_DIR = .objs

DEPFILE_FLAGS = -MMD -MP

WARNINGS_AS_ERRORS = #-Werror #-Wfatal-errors
GCC_EXCLUSIVE_WARNING_OPTIONS = -Wno-unused-but-set-variable

GCC_EXCLUSIVE_WARNING_OPTIONS =  -Wno-unused-but-set-variable
CLANG_EXCLUSIVE_WARNING_OPTIONS =  -Wno-unused-parameter -Wno-unused-variable

ifeq ($(CXX),g++)
EXCLUSIVE_WARNING_OPTIONS = $(GCC_EXCLUSIVE_WARNING_OPTIONS)
else
EXCLUSIVE_WARNING_OPTIONS = $(CLANG_EXCLUSIVE_WARNING_OPTIONS)
endif
# ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer # for debugging, if supported on the OS
WARNINGS = -pedantic -Wall $(WARNINGS_AS_ERRORS) -Wextra $(EXCLUSIVE_WARNING_OPTIONS)

# Flags for compile:
CXXFLAGS += -std=c++14 -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c $(ASANFLAGS)

# Flags for linking:
LDFLAGS += -std=c++14 $(ASANFLAGS)

# Rule for `all` (first/default rule):
all: $(EXE)

# Rule for linking the final executable:
# - $(EXE) depends on all object files in $(OBJS)
# - `patsubst` function adds the directory name $(OBJS_DIR) before every object file
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

# Ensure .objs/ exists:
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/uiuc

# Rules for compiling source code.
# - Every object file is required by $(EXE)
# - Generates the rule requiring the .cpp file of the same name
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Additional dependencies for object files are included in the clang++
# generated .d files (from $(DEPFILE_FLAGS)):
-include $(OBJS_DIR)/*.d
-include $(OBJS_DIR)/uiuc/*.d

TEST_DIR = tests/

$(TEST_DIR):
	@mkdir -p $(TEST_DIR)

test: $(TEST_OBJS) $(TESTS)
	$(LD) $^ $(LDFLAGS) -o $@

# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR) $(CLEAN_RM) *.o *.d *.gch

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
