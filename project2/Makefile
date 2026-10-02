FLAGS = g++ -Wall -std=c++17

driver.out: mytest.o dtree.o
	${FLAGS} mytest.o dtree.o -o driver.out

mytest.o: mytest.cpp
	${FLAGS} -c mytest.cpp

dtree.o: dtree.cpp dtree.h
	${FLAGS} -c dtree.cpp

run: 
	./driver.out

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *.zip

val:
	valgrind ./driver.out

zip:
	zip project2.zip mytest.cpp dtree.h dtree.cpp Makefile