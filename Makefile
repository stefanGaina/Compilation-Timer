#######################################################################################################
# Copyright (C) Compilation-Timer 2024                                                                #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   18.01.2024  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

export COVERAGE_REPORT := coverage_report

GENHTML       = vendor/lcov/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory coverage_report/

INFO_FILES = $(COVERAGE_REPORT)/compilation_timer.info

### MAKE SUBDIRECTORIES ###
all: build doxygen

build:
	$(MAKE) -C compilation-timer

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C compilation-timer

### MAKE UNIT-TESTS ###
ut: ut-clean
	mkdir -p $(COVERAGE_REPORT)
	$(MAKE) -C unit-tests
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CLEAN UNIT-TESTS ###
ut-clean:
	rm -rf $(COVERAGE_REPORT)/*
	$(MAKE) clean -C unit-tests

### MAKE DOXYGEN ###
doxygen:
	doxygen docs/doxygen.conf
