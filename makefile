DIR_INC = ./src
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

BIN_TARGET = ${DIR_BIN}/toCSS

THIS_MAKEFILE=$(abspath $(DIR_BIN)) 

CXXFLAGS= -std=c++11 
${BIN_TARGET}: ${DIR_SRC}/*.cpp
	g++ -o $@ $^ -std=c++11
	echo 'compile successfully, start install ....'
	sudo cp $(BIN_TARGET) /usr/local/bin
	echo 'done'
	echo 'usage: toCSS <file name>.less'
clean:
	rm *.o

