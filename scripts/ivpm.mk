#****************************************************************************
#* ivpm.mk
#*
#* Makefile template for a Chisel project
#****************************************************************************
SCRIPTS_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ROOT_DIR := $(abspath $(SCRIPTS_DIR)/..)
PACKAGES_DIR ?= $(ROOT_DIR)/packages
BUILD_DIR := $(ROOT_DIR)/build
CCRT_INST := $(BUILD_DIR)/ccrt
CCRT_LIB := $(CCRT_INST)/lib
CCRT_INC := $(CCRT_INST)/include
CCRT_SRC := $(ROOT_DIR)/src/ccrt

ifneq (true,$(VERBOSE))
Q=@
endif

# Must support dual modes: 
# - build dependencies if this project is the active one
# - rely on the upper-level makefile to resolve dependencies if we're not
-include $(PACKAGES_DIR)/packages.mk
include $(ROOT_DIR)/etc/ivpm.info
PROJECT := $(name)

SRC_FILES := \
	$(wildcard $(ROOT_DIR)/src/ccrt/*.cpp) \
	$(wildcard $(ROOT_DIR)/src/ccrt/model/*.cpp) \
	$(wildcard $(ROOT_DIR)/src/ccrt/impl/*.cpp)
	
HEADER_INST_FILES := \
$(foreach h,$(wildcard $(CCRT_SRC)/*.h),$(CCRT_INC)/ccrt/$(notdir $(h))) \
$(foreach h,$(wildcard $(CCRT_SRC)/impl/*.h),$(CCRT_INC)/ccrt/impl/$(notdir $(h))) \
$(foreach h,$(wildcard $(CCRT_SRC)/model/*.h),$(CCRT_INC)/ccrt/model/$(notdir $(h))) \
$(CCRT_INC)/ccrt/ccrt \
$(CCRT_INC)/boolector/boolector.h \
$(CCRT_INC)/boolector/btortypes.h


OBJ_FILES := $(foreach o,$(notdir $(SRC_FILES:.cpp=.o)),$(BUILD_DIR)/obj/$(o))

CXXFLAGS += -std=c++11 -I$(ROOT_DIR)/boolector/include
#CXXFLAGS += -g
CXXFLAGS += -O3

CXXFLAGS += $(foreach d,$(SRC_DIRS),-I$(d))

# Include makefiles with dependencies
MK_INCLUDES += $(wildcard $(ROOT_DIR)/mkfiles/*.mk)

include $(MK_INCLUDES)


BOOLECTOR_DIR=boolector-master
BOOLECTOR_ZIP=$(BOOLECTOR_DIR).zip
BOOLECTOR_URL=https://github.com/Boolector/boolector/archive/master.zip

SRC_DIRS += $(ROOT_DIR)/src $(ROOT_DIR)/src/model $(ROOT_DIR)/src/impl

RULES := 1

ifeq (true,$(PHASE2))
build : \
	$(CCRT_LIB)/libccrt.so \
	$(CCRT_LIB)/libboolector.so \
	$(HEADER_INST_FILES)
else
build : $($(PROJECT)_deps)
	$(Q)$(MAKE) -f $(SCRIPTS_DIR)/ivpm.mk PHASE2=true VERBOSE=$(VERBOSE) build
endif

$(CCRT_LIB)/libccrt.so : $(OBJ_FILES)
	$(Q)mkdir -p $(BUILD_DIR)/ccrt/lib
	$(Q)$(CXX) -shared -o $@ $(OBJ_FILES)	
	
$(CCRT_INC)/ccrt/%.h : $(ROOT_DIR)/src/ccrt/%.h
	$(Q)mkdir -p $(CCRT_INC)/ccrt/$(dir $*.h)
	$(Q)cp $(ROOT_DIR)/src/ccrt/$*.h $(CCRT_INC)/ccrt/$(dir $*.h)

$(CCRT_INC)/ccrt/ccrt : $(ROOT_DIR)/src/ccrt/ccrt
	$(Q)mkdir -p $(CCRT_INC)/ccrt
	$(Q)cp $(ROOT_DIR)/src/ccrt/ccrt $(CCRT_INC)/ccrt/ccrt

$(CCRT_INC)/boolector/%.h : \
  $(BUILD_DIR)/boolector/inst/include/boolector/%.h
	$(Q)mkdir -p $(CCRT_INC)/boolector
	$(Q)cp \
          $(BUILD_DIR)/boolector/inst/include/boolector/$*.h \
          $(CCRT_INC)/boolector/$*.h

$(CCRT_LIB)/libboolector.so : $(BUILD_DIR)/boolector.d
	$(Q)mkdir -p $(CCRT_LIB)
	$(Q)cp $(BUILD_DIR)/boolector/inst/lib/libboolector.so $@

$(BUILD_DIR)/boolector/$(BOOLECTOR_DIR)/inst/include/boolector/boolector.h : \
	$(BUILD_DIR)/boolector.d
$(BUILD_DIR)/boolector/$(BOOLECTOR_DIR)/inst/include/boolector/btortypes.h : \
	$(BUILD_DIR)/boolector.d

$(SRC_FILES) : $(BUILD_DIR)/boolector.d

$(BUILD_DIR)/boolector.d : $(PACKAGES_DIR)/$(BOOLECTOR_ZIP)
	$(Q)rm -rf $(BUILD_DIR)/boolector
	$(Q)mkdir -p $(BUILD_DIR)/boolector
	$(Q)mkdir -p $(BUILD_DIR)/include
	$(Q)mkdir -p $(BUILD_DIR)/lib
	$(Q)cd $(BUILD_DIR)/boolector ; unzip -o $(PACKAGES_DIR)/$(BOOLECTOR_ZIP)
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR) ; \
		./contrib/setup-lingeling.sh
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR) ; \
		./contrib/setup-btor2tools.sh
	$(Q)cd $(BUILD_DIR)/boolector/$(BOOLECTOR_DIR) ; \
		./configure.sh --shared --prefix $(BUILD_DIR)/boolector/inst
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

$(BUILD_DIR)/obj/%.o : %.cpp
	$(Q)mkdir -p $(BUILD_DIR)/obj
	$(Q)$(CXX) -c -fPIC -o $@ $(CXXFLAGS) $^

include $(MK_INCLUDES)

-include $(PACKAGES_DIR)/packages.mk
