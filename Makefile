# ====== Configuration ======
SRC = src
LIB_NAME = libEngine.so

target = debug

CFLAGS = -std=c++2b -fpic -g

ifeq ($(target), debug)
  CFLAGS += -Wall -Wextra 
  OBJ = obj/debug
else ifeq ($(target), release)
  CFLAGS += -O3 -DNDEBUG
  OBJ = obj/release
else
  $(error Wrong target)
endif

OUTPUT_DIR = $(OBJ)/output
LIB_DIR = $(OUTPUT_DIR)/lib
INCLUDES_DIR = $(OUTPUT_DIR)/include/engine

LIB = $(LIB_DIR)/$(LIB_NAME)

TEST = test
CONTRIB = contrib

# ====== Setup ======
PCH = $(SRC)/pch.hpp
PCH_COMPILED = $(SRC)/pch.hpp.gch

SRC_LIST = $(shell find $(SRC) -type f -name *.cpp)
HDR_LIST = $(patsubst $(SRC)/%, %, $(shell find $(SRC) -type f -name *.hpp))

CONTRIB = contrib
CONTRIB_SRC = $(wildcard $(CONTRIB)/*/*.cpp)
CONTRIB_HDR = $(wildcard $(CONTRIB)/*/*.h) $(wildcard $(CONTRIB)/*/*.hpp)

SRC_LIST += $(CONTRIB_SRC)
# HDR_LIST += $(CONTRIB_HDR)

INCLUDES_LIST = $(addprefix $(INCLUDES_DIR)/, $(HDR_LIST))
INCLUDES_DIRS = $(sort $(dir $(INCLUDES_LIST)))
OBJ_LIST = $(addprefix $(OBJ)/tmp/, $(patsubst %.cpp, %.o, $(SRC_LIST)))

OBJ_DIRS = $(sort $(dir $(OBJ_LIST)))

.PHONY: all veryclean clean test runTest includes

# ====== Libraries ======
CFLAGS += $(shell pkg-config --cflags sdl2 glew) -I $(CONTRIB) -I $(SRC)
# -lstdc++_libbacktrace
LDFLAGS += $(shell pkg-config --libs sdl2 glew) -ldl -lbfd -lunwind

# ====== Rules ======
all: $(LIB) includes

clean:
	rm -rf $(OUTPUT_DIR)/lib $(OBJ)/tmp/src $(OUTPUT_DIR)/include

veryclean: clean
	rm -rf logs $(OBJ)
	cd $(TEST) && $(MAKE) clean

$(LIB): $(OBJ_LIST) | $(LIB_DIR)
	g++ -std=c++23 -shared -o $@ $^ $(LDFLAGS)

$(LIB_DIR):
	mkdir -p $@

$(OBJ_DIRS):
	mkdir -p $@

$(INCLUDES_DIR):
	mkdir -p $@

includes: $(INCLUDES_LIST)

$(INCLUDES_DIR)/%: $(SRC)/%
	mkdir -p $(dir $@) && cp $< $@

runTest: test
	@LD_LIBRARY_PATH=$(LIB_DIR) $(TEST)/test.out

test: all
	cd $(TEST) && $(MAKE)
	
# ====== Dependency generation ======
DEPFLAGS = -MMD -MF $(@:.o=.d)
DEP := $(patsubst %.o, %.d, $(OBJ_LIST))
-include $(DEP)

$(OBJ)/tmp/%.o: %.cpp $(PCH_COMPILED) | $(OBJ_DIRS)
	g++ $(CFLAGS) -c $< -o $@ $(DEPFLAGS)

$(PCH_COMPILED): $(PCH) | $(INCLUDES_DIR)
	g++ $(CFLAGS) $< -o $@
