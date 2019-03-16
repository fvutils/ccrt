CCRT_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(CCRT_SRC_DIR)

CCRT_SRC = $(wildcard

else # Rules

endif
