CC = /opt/gcc46/bin/g++
FLAGS = -g -lsqlite3 -DDEBUG -Wall;
test:test.o Database.o user.o userMgm.o
	$(CC) -o test test.o Database.o  user.o userMgm.o $(FLAGS)
user.o:../src-srv/user/user.cpp
	$(CC) -c ../src-srv/user/user.cpp -o user.o $(FLAGS)
userMgm.o:../src-srv/user/userMgm.cpp
	$(CC) -c ../src-srv/user/userMgm.cpp -o userMgm.o $(FLAGS)
test.o:test.cpp
	$(CC) -c test.cpp $(FLAGS)
Database.o:Database.cpp
	$(CC) -c Database.cpp $(FLAGS)
clean:
	rm *.o
