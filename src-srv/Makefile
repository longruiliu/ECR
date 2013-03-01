include Makefile.ops
.PHONY:all
all: msgRecord.o
	make -C group/
msgRecord.o: msgRecord.cpp msgRecord.h
	$(CXX) msgRecord.cpp $(CXXFLAG)
