parser.o: parser.cc
	g++ -Iinclude -c parser.cc -Llib -ljson
parserTest: parserTest.cc

