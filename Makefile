CXX = g++
LD  = $(CXX)
ROOTCFLAGS = $(shell root-config --cflags --glibs) -lTree -lTMVA -lMinuit -lXMLParser -lXMLIO -lTreePlayer -lMLP -lProof -lPyROOT -lHistPainter 
CXXFLAGS =  $(ROOTCFLAGS) -Wall -O0 -fPIC -std=c++0x -g
BOOST=-L$(ALRB_BOOST_ROOT)/lib/-lboost_filesystem


all: bin/testCPRW

bin/testCPRW: src/testCPRW.cxx
	mkdir -p bin
	$(LD) $(CXXFLAGS) $(shell rc get_cxxflags) $^ $(shell rc get_all_ldflags) -lweightandoptobs -lgfortran -o $@ 

clean: 
	rm bin/*
