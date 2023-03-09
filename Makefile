BIN := ./bin
INC := ./include
SRC := ./src

CXX := g++ -std=c++17
CFLAGS := -Wall -g

ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTLIBS    := $(shell root-config --libs) -lEG

all: ${BIN}/perform-analysis ${BIN}/clean-noiserms

${BIN}/perform-analysis: ${SRC}/perform-analysis.cpp
	${CXX} -I${INC} ${ROOTCFLAGS} ${SRC}/perform-analysis.cpp -o ${BIN}/perform-analysis ${ROOTLIBS}

${BIN}/clean-noiserms: ${SRC}/clean-noiserms.cpp
	${CXX} -I${INC} ${ROOTCFLAGS} ${SRC}/clean-noiserms.cpp -o ${BIN}/clean-noiserms ${ROOTLIBS}

clean:
	rm ${BIN}/*
