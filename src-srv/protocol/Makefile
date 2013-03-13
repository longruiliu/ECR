ROOT = ../..
INCLUDE = ${ROOT}/include
SERVER_INCLUDE = ../include
LIB = ${ROOT}/lib
CXX = clang++
CXXFLAGS = -Wall

all: protocol.o
	echo ${INCLUDE}; ${CXX} protocol.o -ljson -L${LIB}

protocol.o: protocol.cc
	${CXX} ${CXXFLAGS} -I${INCLUDE} -I${SERVER_INCLUDE} -c protocol.cc

test: protocolTest.cc
	${CXX} ${CXXFLAGS} -I${INCLUDE} -L${LIB} protocolTest.cc -o protocolTest -ljson

clean:
	rm *.o protocolTest
