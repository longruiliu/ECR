protocol.o: protocol.cc
	clang++ -c protocol.cc -Iinclude -g -Wall

protocol: protocol.o
	clang++ -Llib protocol.o -ljson -o protocol -g -Wall

clean:
	rm *.o