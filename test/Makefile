# ====== Configuration ======
SRC = src
EXEC = test.out

target = debug

CFLAGS = -std=c++2b -g

ifeq ($(target), debug)
  CFLAGS += -Wall -Wextra
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

# stack trace not working...
# -lstdc++_libbacktrace
LDFLAGS = -l$(LIB) -lbfd -lunwind
CFLAGS += -I$(SRC)

.PHONY: all clean test

# ====== Rules ======
all: $(EXEC)

clean:
	rm -rf obj $(EXEC)

$(EXEC): $(OBJ_LIST)
	g++ -std=c++23 -o $@ $^ -L $(LIB_DIR) $(LDFLAGS) 

$(OBJ_DIRS):
	mkdir -p $@

# ====== Dependency generation ======
DEPFLAGS = -MMD -MF $(@:.o=.d)
DEP := $(patsubst %.o, %.d, $(OBJ_LIST))
-include $(DEP)

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ_DIRS)
	g++ $(CFLAGS) -c $< -o $@ $(DEPFLAGS)

