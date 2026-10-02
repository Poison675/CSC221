CXX = g++
FLAGS = -Wall -std=c++17
OBJS = mytest.o dtree.o utree.o
PROJ = mytest.out
NAME = project3

${PROJ}: ${OBJS}
	${CXX} ${FLAGS} ${OBJS} -o $@

mytest.o: mytest.cpp
	${CXX} ${FLAGS} -c $<

dtree.o: dtree.cpp dtree.h
	${CXX} ${FLAGS} -c $<

utree.o: utree.cpp utree.h
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
	zip ${NAME}.zip utree.cpp utree.h mytest.cpp