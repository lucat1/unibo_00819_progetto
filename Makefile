SRC_DIR  = src
INT_DIR  = build
TEST_DIR = build/test
TARGET   = overengineered

CXX = g++
## -MMD creates dependency list, but ignores system includes ## -MF specifies where to create the dependency file name
## -MP creates phony targets for headers (deals with deleted headers after
##  obj file has been compiled)
## -MT specifies the dependency target (path qualified obj file name)
CXXFLAGS = -std=c++11 -MT $@ -MMD -MP -MF $(@:.o=.d) -Wall -Werror
LDFLAGS = -lstdc++
# conditional linker flags based on OS (Linux (tested on Ubuntu, Elementary and void), Darwin = MacOS)
UNAME := $(shell uname)

HAS_CURSESW6 := $(shell command -v ncursesw6-config 2> /dev/null)
HAS_CURSESW5 := $(shell command -v ncursesw5-config 2> /dev/null)

# use ncursesw6-config utility to find libraries when available
# therwhise go for a best guess
ifdef HAS_CURSESW6
CXXFLAGS += $(shell ncursesw6-config --cflags)
LDFLAGS += $(shell ncursesw6-config --libs)
STATICNCURSES = $(shell ncursesw6-config --libdir)/libncurses.a
else
	ifdef HAS_CURSESW5
	CXXFLAGS += $(shell ncursesw5-config --cflags)
	LDFLAGS += $(shell ncursesw5-config --libs)
	STATICNCURSES = $(shell ncursesw5-config --libdir)/libncurses.a
	else
	CXXFLAGS += -D_XOPEN_SOURCE_EXTENDED
	LDFLAGS += -lncurses -lncursesw
	# mock of a likely location on Darwin for the ncurses static binary
	STATICNCURSES = /usr/local/Cellar/ncurses/6.2/lib/libncurses.a
	endif
endif

# Things to build
ALL_FILES := $(wildcard $(SRC_DIR)/**/**/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
ALL_HEADER_FILES := $(wildcard $(SRC_DIR)/**/**/*.hpp) $(wildcard $(SRC_DIR)/**/*.hpp) $(wildcard $(SRC_DIR)/*.hpp)
CPP_FILES := $(filter-out %.test.cpp, $(ALL_FILES))
TEST_FILES := $(filter %.test.cpp, $(ALL_FILES))

ALL_OBJ_FILES := $(ALL_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
CPP_OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
TEST_OBJ_FILES := $(TEST_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
AUX_OBJ_FILES := $(filter-out build/main.o, $(CPP_OBJ_FILES))

DEP_FILES := $(ALL_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.d)
TEST_TARGETS := $(TEST_OBJ_FILES:$(INT_DIR)/%.o=$(TEST_DIR)/%)

SUB_FOLDERS := $(filter-out src, $(patsubst src/%,%, $(shell find src -type d)))
OBJ_FOLDERS := $(addprefix build/, $(SUB_FOLDERS)) $(addprefix build/test/, $(SUB_FOLDERS))
.PHONY: test debug info clean format run $(TEST_TARGETS) static-darwin

all: info $(TARGET)
test: info $(TEST_TARGETS)
debug: CXXFLAGS += -ggdb
debug: clean all test
static-linux: LDFLAGS += -static -static-libstdc++ -static-libgcc
static-linux: info all

info:
	@echo
	@echo "CXX = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo

clean:
	@echo -e "RMRF\tbuild $(TARGET)"
	@rm -rf build $(TARGET)

format:
	clang-format -i $(ALL_FILES) $(ALL_HEADER_FILES)

run: all
	@echo -e "RUN\t$(TARGET)"
	@./$(TARGET)

$(TEST_TARGETS): $(TEST_DIR)/%: $(INT_DIR)/%.o | $(ALL_OBJ_FILES)
	@echo -e "LD\t$<"
	@$(CXX) $^ $(AUX_OBJ_FILES) $(LDFLAGS) -o $@
	@echo -e "RUN\t$@"
	@$@
	@echo -e "SUCCESS\t$@"

$(ALL_OBJ_FILES): $(INT_DIR)/%.o: $(SRC_DIR)/%.cpp $(INT_DIR)/%.d | $(OBJ_FOLDERS)
	@echo -e "CC\t$<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(CPP_OBJ_FILES)
	@echo -e "LD\t$@"
	@$(CXX) $^ $(LDFLAGS) -o $@

static-darwin: $(CPP_OBJ_FILES)
	@echo -e "LD\t$@"
	$(CXX) $(STATICNCURSES) $^ -o $(TARGET)

$(DEP_FILES): $(INT_DIR)/%.d: ;

$(OBJ_FOLDERS):
	@echo -e "MKDIR\t$@"
	@mkdir -p $@

-include $(DEP_FILES)
