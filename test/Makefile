.PHONY : all test prepare_gtest
GTEST_DIR = ./googletest/googletest
BUILD_DIR = ./obj
CXX       ?= g++
AR        = ar
CXX_FLAGS = -g -std=c++11 -lncurses -DTEST=1 -I../

prepare_gtest: $(BUILD_DIR) $(BUILD_DIR)/libgtest.a

$(BUILD_DIR):
	@mkdir obj

$(BUILD_DIR)/libgtest.a: $(BUILD_DIR)/gtest-all.o
	@$(AR) -rv $(BUILD_DIR)/libgtest.a $(BUILD_DIR)/gtest-all.o

$(BUILD_DIR)/gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	@$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) \
    	-pthread -c $(GTEST_DIR)/src/gtest-all.cc -o $(BUILD_DIR)/gtest-all.o

run:
	@$(CXX) $(CXX_FLAGS) -isystem $(GTEST_DIR)/include \
		-pthread test_calculator.cpp $(BUILD_DIR)/libgtest.a \
    	-o $(BUILD_DIR)/test_calculator
	./$(BUILD_DIR)/test_calculator

test: prepare_gtest run
all: test
