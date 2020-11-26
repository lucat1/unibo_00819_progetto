SRC_DIR = src
INT_DIR = build
TMP_DIR = tmp
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
CPP_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp) 
OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.o)
DEP_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(INT_DIR)/%.d)
OBJ_FOLDERS := build/engine build/game build/world build/data

.PHONY: all clean run

all: $(TARGET)

run: all
	@./$(TARGET)

$(OBJ_FILES): $(INT_DIR)/%.o: $(SRC_DIR)/%.cpp $(INT_DIR)/%.d | $(OBJ_FOLDERS)
	@echo "CC\t$<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJ_FILES)
	@echo "LD\t$<"
	@$(CXX) $(LDFLAGS) -o $@ $^

$(DEP_FILES): $(INT_DIR)/%.d: ;

$(OBJ_FOLDERS):
	@echo "MKDIR\t$@"
	@mkdir -p $@

clean:
	rm -rf build $(TMP_DIR) $(TARGET)

-include $(DEP_FILES)
