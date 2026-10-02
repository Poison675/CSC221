# setting flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

all: driver.o Point.o
	$(CXX) $(CXXFLAGS) driver.o Point.o -o output.out

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

Point.o: Point.h
	$(CXX) $(CXXFLAGS) -c Point.h

run:
	./output.out

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#
