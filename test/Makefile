# ====== Configuration ======
SRC = src
EXEC = test.out

target = debug

CFLAGS = -std=gnu++2b -I$(SRC)

ifeq ($(target), debug)
  CFLAGS += -g -Wall -Wextra -Wshadow
  OBJ = obj/debug
else ifeq ($(target), release)
  CFLAGS += -O3 -DNDEBUG
  OBJ = obj/release
else
  $(error Wrong target)
endif

LIB_DIR = ../$(OBJ)/output/lib
LIB = Engine
CFLAGS += -I../$(OBJ)/output/include

# ====== Setup ======
SRC_LIST = $(shell find $(SRC) -type f -name *.cpp)
OBJ_LIST = $(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(SRC_LIST:$(SRC)/%=%)))

OBJ_DIRS = $(sort $(dir $(OBJ_LIST)))

.PHONY: all clean test

# ====== Rules ======
all: $(EXEC)

clean:
	rm -rf obj $(EXEC)

$(EXEC): $(OBJ_LIST)
	g++ -L $(LIB_DIR) -l $(LIB) -o $@ $^

$(OBJ_DIRS):
	mkdir -p $@

# ====== Dependency generation ======
DEPFLAGS = -MMD -MF $(@:.o=.d)
DEP := $(patsubst %.o, %.d, $(OBJ_LIST))
-include $(DEP)

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ_DIRS)
	g++ $(CFLAGS) -c $< -o $@ $(DEPFLAGS)

