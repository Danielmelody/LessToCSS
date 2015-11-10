DIR_INC = ./src
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

BIN_TARGET = ${DIR_BIN}/toCSS

CXXFLAGS= -std=c++11 
${BIN_TARGET}: ${DIR_SRC}/*.cpp
	g++ -o $@ $^ -std=c++11
clean:
	rm *.o

