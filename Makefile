BIN := ./bin
INC := ./include
SRC := ./src

CXX := g++ -std=c++17
CFLAGS := -Wall -g

ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTLIBS    := $(shell root-config --libs) -lEG

all: ${BIN}/calculate-amplitude

${BIN}/calculate-amplitude: ${SRC}/calculate-amplitude.cpp
	${CXX} -I${INC} ${ROOTCFLAGS} ${SRC}/calculate-amplitude.cpp -o ${BIN}/calculate-amplitude ${ROOTLIBS}

clean:
	rm ${BIN}/*
