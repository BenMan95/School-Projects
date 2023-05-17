CXX=g++
CXXFLAGS = -std=c++14 -g
DEP_DIR= ../dependencies

all: queue_unittest queue

queue: queue.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -Iinclude -L$(DEP_DIR)/lib queue.o main.cc -o $@

queue_unittest: queue.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -Iinclude -L$(DEP_DIR)/lib queue_unittest.cc queue.o -lgtest_main -lgtest -lgmock -pthread -o $@

clean:
	rm -f queue_unittest queue
