all: driver.o Point.o Triangle.o
        g++ -ansi -Wall Point.o Triangle.o -o driver.out

driver.o: driver.cpp Triangle.h Point.h
        g++ -ansi -Wall -c driver.cpp

Triangle.o: Triangle.cpp Triangle.h
        g++ -ansi -Wall -c Triangle.cpp

Point.o: Point.h
        g++ -ansi -Wall -c Point.h

clean:
        rm -f *.o output *~ *.gch