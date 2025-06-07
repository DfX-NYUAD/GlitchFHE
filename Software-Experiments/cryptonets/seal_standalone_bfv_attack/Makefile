# directories
E3ROOT=$(abspath ./)
PROJECTDIR=$(abspath ./)
CRYTONETDIR=${PROJECTDIR}
DATADIR=${CRYTONETDIR}/data

# input data
IN=${DATADIR}/x_test.tmp
OUT=${DATADIR}/y_test.tmp
W1=${DATADIR}/W1.tmp
W2=${DATADIR}/W4.tmp
W3=${DATADIR}/W8.tmp
B1=${DATADIR}/b1.tmp
B2=${DATADIR}/b4.tmp
B3=${DATADIR}/b8.tmp
LOGN=13

# compiler, flags, incs, and libs
CC=g++
FLAGS=-O2 -std=c++17
INCS=-I${E3ROOT}/./seal_unx/include
CPPS=io.cpp numpy.cpp
LIBS=${E3ROOT}/./seal_unx/target/libseal.a
DEFINES=

all: compile

%: %.cpp
	${CC} ${INCS} ${FLAGS} -o $@.exe $< ${CPPS} ${LIBS} ${DEFINES}

clean:
	rm -f *.o *.exe *.tmp

compile: main

run:
	./main.exe ${IN} ${W1} ${W2} ${W3} ${B1} ${B2} ${B3} ${OUT} ${LOGN}
