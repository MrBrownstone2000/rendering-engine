# ====== Projets ======
PROJECTS = sandbox test
PROJECTS_RUN = $(addsuffix Run, $(PROJECTS))
PROJECTS_CLEAN = $(addsuffix Clean, $(PROJECTS))
PROJECTS_CLEAN_ALL = $(addsuffix CleanAll, $(PROJECTS))

# ====== Configuration ======
SRC = src
LIB_NAME = libEngine.so

target = debug

CFLAGS = -Wall -Wextra -std=c++2b -fpic -g

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
LIB_DIR = $(OUTPUT_DIR)/lib
INCLUDES_DIR = $(OUTPUT_DIR)/include/engine

LIB = $(LIB_DIR)/$(LIB_NAME)

TEST = test
CONTRIB = contrib

# ====== Setup ======
PCH = $(SRC)/pch.hpp
PCH_DIR = $(OBJ)/tmp
PCH_COMPILED = $(PCH_DIR)/pch.hpp.gch

SRC_LIST = $(shell find $(SRC) -type f -name "*.cpp")
HDR_LIST = $(patsubst $(SRC)/%, %, $(shell find $(SRC) -type f -name "*.hpp" ! -name $(notdir $(PCH))))

CONTRIB = contrib
CONTRIB_SRC = $(wildcard $(CONTRIB)/*/*.cpp)
CONTRIB_HDR = $(wildcard $(CONTRIB)/*/*.h) $(wildcard $(CONTRIB)/*/*.hpp)

SRC_LIST += $(CONTRIB_SRC)
# HDR_LIST += $(CONTRIB_HDR)

INCLUDES_LIST = $(addprefix $(INCLUDES_DIR)/, $(HDR_LIST))
INCLUDES_DIRS = $(sort $(dir $(INCLUDES_LIST)))
OBJ_LIST = $(addprefix $(OBJ)/tmp/, $(patsubst %.cpp, %.o, $(SRC_LIST)))

OBJ_DIRS = $(sort $(dir $(OBJ_LIST)))

.PHONY: all veryclean clean includes $(PROJECTS) $(PROJECTS_RUN)

# ====== Libraries ======
CFLAGS += -I $(PCH_DIR) $(shell pkg-config --cflags sdl2 glew) -I $(CONTRIB) -I $(SRC) -I $(CONTRIB)/imgui
# -lstdc++_libbacktrace
LDFLAGS += $(shell pkg-config --libs sdl2 glew) -ldl -lbfd -lunwind

# ====== Rules ======
engine: $(LIB) includes

all: engine $(PROJECTS)

$(PROJECTS): engine
	cd $@ && make

$(PROJECTS_RUN): engine
	cd $(shell target=$@ && echo $${target%"Run"}) && make run

$(PROJECTS_CLEAN):
	cd $(shell target=$@ && echo $${target%"Clean"}) && make clean

$(PROJECTS_CLEAN_ALL):
	cd $(shell target=$@ && echo $${target%"CleanAll"}) && make cleanAll

clean:
	rm -rf $(OUTPUT_DIR)/lib $(OBJ)/tmp/src $(OUTPUT_DIR)/include

veryclean: clean
	rm -rf logs $(OBJ)

cleanAll: veryclean $(PROJECTS_CLEAN_ALL)
	rm -rf obj

$(LIB): $(OBJ_LIST) | $(LIB_DIR)
	g++ -std=c++23 -shared -o $@ $^ $(LDFLAGS)

$(LIB_DIR):
	mkdir -p $@

$(PCH_DIR):
	mkdir -p $@

$(OBJ_DIRS):
	mkdir -p $@

$(INCLUDES_DIR):
	mkdir -p $@

includes: $(INCLUDES_LIST)

$(INCLUDES_DIR)/%: $(SRC)/%
	mkdir -p $(dir $@) && cp $< $@
	
# ====== Dependency generation ======
DEPFLAGS = -MMD -MF $(@:.o=.d)
DEP := $(patsubst %.o, %.d, $(OBJ_LIST))
-include $(DEP)

$(OBJ)/tmp/%.o: %.cpp $(PCH_COMPILED) | $(OBJ_DIRS)
	g++ $(CFLAGS) -c $< -o $@ $(DEPFLAGS)

$(PCH_COMPILED): $(PCH) | $(PCH_DIR)
	g++ $(CFLAGS) $< -o $@
