#****************************************************************************
#* ivpm.mk
#*
#* Makefile template for a Chisel project
#****************************************************************************
SCRIPTS_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ROOT_DIR := $(abspath $(SCRIPTS_DIR)/..)
PACKAGES_DIR ?= $(ROOT_DIR)/packages
BUILD_DIR := $(ROOT_DIR)/build

ifneq (true,$(VERBOSE))
Q=@
endif

# Must support dual modes: 
# - build dependencies if this project is the active one
# - rely on the upper-level makefile to resolve dependencies if we're not
-include $(PACKAGES_DIR)/packages.mk
include $(ROOT_DIR)/etc/ivpm.info
PROJECT := $(name)

SRC_FILES := $(wildcard $(ROOT_DIR)/src/*.cpp)
CXXFLAGS += -std=c++11 -I$(ROOT_DIR)/boolector/include
#CXXFLAGS += -g
CXXFLAGS += -O3

# Include makefiles with dependencies
MK_INCLUDES += $(wildcard $(ROOT_DIR)/mkfiles/*.mk)

include $(MK_INCLUDES)


BOOLECTOR_DIR=boolector-master
BOOLECTOR_ZIP=$(BOOLECTOR_DIR).zip
BOOLECTOR_URL=https://github.com/Boolector/boolector/archive/master.zip

SRC_DIRS += $(ROOT_DIR)/src

RULES := 1

ifeq (true,$(PHASE2))
build : $(BUILD_DIR)/ccrt.d
else
build : $($(PROJECT)_deps)
	$(Q)$(MAKE) -f $(SCRIPTS_DIR)/ivpm.mk PHASE2=true VERBOSE=$(VERBOSE) build
endif

$(BUILD_DIR)/ccrt.d : $(notdir $(SRC_FILES:.cpp=.o))
	$(Q)$(LD) -r -o libccrt.so $(notdir $(SRC_FILES:.cpp=.o))
	

$(SRC_FILES) : $(BUILD_DIR)/boolector.d

$(BUILD_DIR)/boolector.d : $(PACKAGES_DIR)/$(BOOLECTOR_ZIP)
	$(Q)rm -rf $(BUILD_DIR)/boolector
	$(Q)mkdir -p $(BUILD_DIR)/boolector
	$(Q)cd $(BUILD_DIR)/boolector ; unzip -o $(PACKAGES_DIR)/$(BOOLECTOR_ZIP)
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR) ; ./contrib/setup-lingeling.sh
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR) ; ./contrib/setup-btor2tools.sh
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR) ; ./configure.sh \
		--shared --prefix $(ROOT_DIR)/boolector
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR)/build ; $(MAKE)
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR)/build ; $(MAKE) install
	$(Q)touch $@

$(PACKAGES_DIR)/$(BOOLECTOR_ZIP) :
	$(Q)mkdir -p $(PACKAGES_DIR)
	$(Q)wget -O $@ $(BOOLECTOR_URL) || (rm -f $@; exit 1)

release : build
	$(Q)rm -rf $(ROOT_DIR)/build
	$(Q)mkdir -p $(ROOT_DIR)/build/$(PROJECT)
	$(Q)cp -r \
          $(ROOT_DIR)/lib \
          $(ROOT_DIR)/etc \
          $(ROOT_DIR)/build/$(PROJECT)
	$(Q)cd $(ROOT_DIR)/build ; \
		tar czf $(PROJECT)-$(version).tar.gz $(PROJECT)
	$(Q)rm -rf $(ROOT_DIR)/build/$(PROJECT)

vpath %.cpp $(SRC_DIRS)

include $(MK_INCLUDES)

-include $(PACKAGES_DIR)/packages.mk
