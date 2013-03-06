protocol.o: protocol.cc
	g++ -c protocol.cc -Iinclude -Llib/json -ljson
clean:
	rm *.o