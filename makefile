CC=g++
LIBS=-lhdf5 -lhdf5_cpp -fopenmp
STD=-O3

all:	lib Pulsar

Pulsar:	Pulsar/main.cpp
		${CC} Pulsar/main.cpp -lT3nsors ${LIBS} ${STD} -o Pulsar.o
alib:	T3nsors/*.h T3nsors/*.cpp
		${CC} -c T3nsors/*.cpp ${STD}
		ar rcs libT3nsors.a *.o
lib:	T3nsors/*.h T3nsors/*.cpp
		${CC} T3nsors/*.cpp -shared -fPIC ${LIBS} ${STD} -o libT3nsors.so
