SRC_DIR = src
INT_DIR = build
TEST_DIR = build/test
TARGET  = game

CXX = g++
## -MMD creates dependency list, but ignores system includes
## -MF specifies where to create the dependency file name
## -MP creates phony targets for headers (deals with deleted headers after
##  obj file has been compiled)
## -MT specifies the dependency target (path qualified obj file name)
DEP_FLAGS = -MT $@ -MMD -MP -MF $(@:.o=.d)
CXXFLAGS = $(DEP_FLAGS) -Wall -Werror
LDFLAGS = -lstdc++ -lcurses

# Things to build
ALL_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
CPP_FILES := $(filter-out %.test.cpp, $(ALL_FILES))
TEST_FILES := $(filter %.test.cpp, $(ALL_FILES))

ALL_OBJ_FILES := $(ALL_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
CPP_OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
TEST_OBJ_FILES := $(TEST_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)

DEP_FILES := $(ALL_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.d)
TEST_TARGETS := $(TEST_OBJ_FILES:$(INT_DIR)/%.o=$(TEST_DIR)/%)

SUB_FOLDERS := engine game world data
OBJ_FOLDERS := $(addprefix build/, $(SUB_FOLDERS)) $(addprefix build/test/, $(SUB_FOLDERS))

.PHONY: clean run
all: $(TARGET)
run: all
	@./$(TARGET)

clean:
	rm -rf build $(TARGET)

test: $(TEST_TARGETS)

$(TEST_TARGETS): $(TEST_DIR)/%: $(INT_DIR)/%.o | $(ALL_OBJ_FILES)
	@echo "LD\t$<"
	@$(CXX) $(LDFLAGS) -o $@ $(filter-out, $(TARGET), $(CPP_OBJ_FILES)) $^ 
	@echo "RUN\t$@"
	@$@
	@echo "SUCCESS\t$@"

$(ALL_OBJ_FILES): $(INT_DIR)/%.o: $(SRC_DIR)/%.cpp $(INT_DIR)/%.d | $(OBJ_FOLDERS)
	@echo "CC\t$<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(CPP_OBJ_FILES)
	@echo "LD\t$<"
	@$(CXX) $(LDFLAGS) -o $@ $^

$(DEP_FILES): $(INT_DIR)/%.d: ;

$(OBJ_FOLDERS):
	@echo "MKDIR\t$@"
	@mkdir -p $@

-include $(DEP_FILES)
