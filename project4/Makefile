CXX = g++
FLAGS = -Wall -std=c++17
OBJS = mytest.o rqueue.o
PROJ = mytest.out
NAME = project4

${PROJ}: ${OBJS}
	${CXX} ${FLAGS} ${OBJS} -o $@

mytest.o: mytest.cpp
	${CXX} ${FLAGS} -c $<

rqueue.o: rqueue.cpp rqueue.h
	${CXX} ${FLAGS} -c $<


run: 
	./${PROJ}

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *.zip

val:
	valgrind ./${PROJ}

zip:
	zip ${NAME}.zip rqueue.cpp rqueue.h mytest.cpp Makefile
