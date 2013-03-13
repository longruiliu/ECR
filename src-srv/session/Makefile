CC = clang++

main: main.cpp session.o
	$(CC) -o main main.cpp session.o

session.o: session.cpp session.h
	$(CC) -c session.cpp

