BIN := ./bin
INC := ./include
SRC := ./src

CXX := g++ -std=c++17
CFLAGS := -Wall -g

ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTLIBS    := $(shell root-config --libs) -lEG

all: ${BIN}/perform-analysis

${BIN}/perform-analysis: ${SRC}/perform-analysis.cpp
	${CXX} -I${INC} ${ROOTCFLAGS} ${SRC}/perform-analysis.cpp -o ${BIN}/perform-analysis ${ROOTLIBS}

clean:
	rm ${BIN}/*
