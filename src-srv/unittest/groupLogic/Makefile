include ../../Makefile.ops
.PHONY: all
all: 
	make -C ../../
	cp ../../msgRecord.o .
	make -C ../../group
	cp ../../group/*.o .
	$(CXX) main.cpp trunc_network.cpp trunc_user.cpp $(CXXFLAG)
	$(CXX) *.o $(LINKERFLAG)
