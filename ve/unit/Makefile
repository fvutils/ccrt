VE_UNIT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PACKAGES_DIR ?= $(abspath $(VE_UNIT_DIR)/../../packages)
CCRT_DIR ?= $(abspath $(VE_UNIT_DIR)/../..)

include $(PACKAGES_DIR)/packages.mk

CXXFLAGS += -std=c++11
CXXFLAGS += -g
CXXFLAGS += -O3

SRC_DIRS += $(VE_UNIT_DIR)/src
SRC_DIRS += $(CCRT_DIR)/src
SRC_DIRS += $(CCRT_DIR)/boolector/include

UNIT_TEST_SRC_FILES = $(wildcard $(VE_UNIT_DIR)/src/*.cpp)
UNIT_TEST_SRCS = $(notdir $(UNIT_TEST_SRC_FILES))
CXXFLAGS += $(foreach d,$(SRC_DIRS),-I$(d))

ifneq (,$(GTEST_FILTER))
ARGS += --gtest_filter=$(GTEST_FILTER)
endif

RULES := 1

all : 
	mkdir -p build
	$(MAKE) -C build -f $(VE_UNIT_DIR)/Makefile ve_unit
	export LD_LIBRARY_PATH=$(CCRT_DIR)/boolector/lib:$(VE_UNIT_DIR)/build ; \
		./build/ve_unit $(ARGS)

debug : 
	mkdir -p build
	cd build ; $(MAKE) -f $(VE_UNIT_DIR)/Makefile ve_unit
	export LD_LIBRARY_PATH=$(CCRT_DIR)/boolector/lib:$(VE_UNIT_DIR)/build ; \
		gdb --args ./build/ve_unit $(ARGS)

valgrind : 
	mkdir -p build
	cd build ; $(MAKE) -f $(VE_UNIT_DIR)/Makefile ve_unit
	export LD_LIBRARY_PATH=$(CCRT_DIR)/boolector/lib:$(VE_UNIT_DIR)/build ; \
		valgrind --tool=memcheck ./build/ve_unit

vpath %.cpp $(SRC_DIRS)
vpath %.cc $(SRC_DIRS)

$(UNIT_TEST_SRC_FILES) : ccrt.d

ve_unit : $(UNIT_TEST_SRCS:.cpp=.o) libgoogletest.o
	$(CXX) -o $@ $(UNIT_TEST_SRCS:.cpp=.o) \
		libgoogletest.o \
		-I$(CCRT_DIR)/boolector/include -I$(CCRT_DIR)/src \
		-L$(CCRT_DIR)/boolector/lib -L. -lboolector -lccrt -lpthread

ccrt.d : 
	$(MAKE) -f $(CCRT_DIR)/scripts/ivpm.mk

clean :
	rm -rf *.o *.so ve_unit build

include $(PACKAGES_DIR)/packages.mk

