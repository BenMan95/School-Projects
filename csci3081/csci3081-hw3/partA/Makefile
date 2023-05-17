CXX=g++
CXXFLAGS = -std=c++14 -g
DEP_DIR= ../dependencies

##### EDIT ME!!! #####################
MAINEXEFILE = date.correct.cc
######################################
MAINTESTFILE = date_unittest.cc
LABTESTEXE = date_unittest
LABEXE = date

all: ${LABEXE} ${LABTESTEXE}

${LABEXE}:
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -Iinclude -L$(DEP_DIR)/lib main.cc $(MAINEXEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

${LABTESTEXE}: 
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -Iinclude -L$(DEP_DIR)/lib $(MAINTESTFILE) $(MAINEXEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

test: ${LABTESTEXE}

clean:
	rm -f ${LABEXE}
	rm -f ${LABTESTEXE}
	rm -rf *.o
