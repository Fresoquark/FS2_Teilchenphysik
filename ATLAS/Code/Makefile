ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)

CXX = g++
RM  = rm -f

CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += -Wall -Wno-deprecated -ggdb -fPIC
LIBS     += $(ROOTLIBS) -lTreePlayer -lMinuit

SRC = $(wildcard *.cxx)
OBJ = $(patsubst %.cxx, %.o, $(SRC))

RUN = $(wildcard *.C)
EXE = $(patsubst %.C, %.exe, $(RUN))

GARBAGE = $(OBJ) $(EXE)

all : $(OBJ) $(EXE)

%.exe : %.C $(OBJ)
	@echo "creating " $@
	@$(CXX) $+ -o $@ $(CXXFLAGS) $(LIBS)

%.o : %.cxx %.h
	@echo "creating " $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@$(RM) $(GARBAGE)
