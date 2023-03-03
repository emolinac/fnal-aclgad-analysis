BIN := ./bin
INC := ./include
SRC := ./src

CXX := g++ -std=c++17
CFLAGS := -Wall -g

ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTLIBS    := $(shell root-config --libs) -lEG

all: ${BIN}/calculate-signaltonoise

${BIN}/calculate-signaltonoise: ${SRC}/calculate-signaltonoise.cpp
	${CXX} -I${INC} ${ROOTCFLAGS} ${SRC}/calculate-signaltonoise.cpp -o ${BIN}/calculate-signaltonoise ${ROOTLIBS}

clean:
	rm ${BIN}/*
