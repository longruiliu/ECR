LIBS = -lpthread
CC = g++
CFLAGS = -g -Wall -DDEBUG
OBJS = network.o ecr.o
TARGET = ECR

${TARGET}:${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${TARGET}
	
%.o:%.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY:clean
clean:
	-rm *.o ${TARGET} 

