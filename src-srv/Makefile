include Makefile.ops
.PHONY:all

all: msgRecord.o protocol.o
	make -C group/

msgRecord.o: msgRecord.cpp msgRecord.h
	$(CXX) msgRecord.cpp $(CXXFLAG)

protocol.o:
	@if [ -d protocol ]; \
		then \
		(cd protocol && make protocol.o); \
	fi
