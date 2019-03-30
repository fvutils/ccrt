VE_UNIT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PACKAGES_DIR ?= $(abspath $(VE_UNIT_DIR)/../../packages)

include $(PACKAGES_DIR)/packages.mk

CXXFLAGS += -std=c++11 -g

SRC_DIRS += $(VE_UNIT_DIR)/src

UNIT_TEST_SRC_FILES = $(wildcard $(VE_UNIT_DIR)/src/*.cpp)
UNIT_TEST_SRCS = $(notdir $(UNIT_TEST_SRC_FILES))
CXXFLAGS += $(foreach d,$(SRC_DIRS),-I$(d))

RULES := 1

all : ve_unit
	export LD_LIBRARY_PATH=../../boolector/lib:. ; ./ve_unit

debug : ve_unit
	export LD_LIBRARY_PATH=../../boolector/lib:. ; gdb --args ./ve_unit

valgrind : ve_unit
	export LD_LIBRARY_PATH=../../boolector/lib:. ; \
		valgrind --tool=memcheck ./ve_unit

vpath %.cpp $(SRC_DIRS)
vpath %.cc $(SRC_DIRS)

$(UNIT_TEST_SRC_FILES) : ccrt.d

ve_unit : $(UNIT_TEST_SRCS:.cpp=.o) libgoogletest.o
	$(CXX) -o $@ $(UNIT_TEST_SRCS:.cpp=.o) \
		libgoogletest.o \
		-I../../boolector/include -I../../src \
		-L../../boolector/lib -L. -lboolector -lccrt -lpthread

ccrt.d : 
	$(MAKE) -f ../../scripts/ivpm.mk

clean :
	rm -rf *.o *.so ve_unit

include $(PACKAGES_DIR)/packages.mk

