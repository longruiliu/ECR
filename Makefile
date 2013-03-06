protocol.o: protocol.cc
	g++ -c protocol.cc -Iinclude -g

protocol: protocol.o
	g++ -Llib protocol.o -ljson -o protocol -g

clean:
	rm *.o