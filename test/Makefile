# ====== Configuration ======
SRC = src
EXEC_NAME = test.out

target = debug

CFLAGS = -Wall -Wextra -std=c++2b -g

ifeq ($(target), debug)
  CFLAGS += 
  OBJ = obj/debug
else ifeq ($(target), release)
  CFLAGS += -O3 -DNDEBUG
  OBJ = obj/release
else
  $(error Wrong target)
endif

OUTPUT_DIR = $(OBJ)/output
EXEC = $(OUTPUT_DIR)/$(EXEC_NAME)

LIB_DIR = ../$(OBJ)/output/lib
LIB = Engine
CFLAGS += -I../$(OBJ)/output/include

# ====== Setup ======
SRC_LIST = $(shell find $(SRC) -type f -name *.cpp)
OBJ_LIST = $(addprefix $(OBJ)/tmp/, $(patsubst %.cpp, %.o, $(SRC_LIST:$(SRC)/%=%)))

OBJ_DIRS = $(sort $(dir $(OBJ_LIST)))

LDFLAGS = -l$(LIB) -lOpenImageIO
CFLAGS += -I$(SRC)

.PHONY: all clean run cleanAll

# ====== Rules ======
all: $(EXEC)

run: $(EXEC)
	LD_LIBRARY_PATH=$(LIB_DIR) ./$(EXEC)

clean:
	rm -rf $(OBJ) logs 

cleanAll:
	rm -rf obj logs

$(EXEC): $(OBJ_LIST) | $(OUTPUT_DIR)
	g++ -std=c++23 -o $@ $^ -L $(LIB_DIR) $(LDFLAGS) 

$(OUTPUT_DIR):
	mkdir -p $@

$(OBJ_DIRS):
	mkdir -p $@

# ====== Dependency generation ======
DEPFLAGS = -MMD -MF $(@:.o=.d)
DEP := $(patsubst %.o, %.d, $(OBJ_LIST))
-include $(DEP)

$(OBJ)/tmp/%.o: $(SRC)/%.cpp | $(OBJ_DIRS)
	g++ $(CFLAGS) -c $< -o $@ $(DEPFLAGS)

