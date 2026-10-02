FLAGS = g++ -Wall -std=c++17

driver.out: buffer.o bufferlist.o driver2.o
	$(FLAGS) driver2.o buffer.o bufferlist.o -o driver.out

buffer.o: buffer.cpp buffer.h
	$(FLAGS) -c buffer.cpp

bufferlist.o: bufferlist.cpp bufferlist.h
	$(FLAGS) -c bufferlist.cpp

driver2.o: driver2.cpp
	$(FLAGS) -c driver2.cpp

run:
	./driver.out

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *.zip

zip:
	zip -r buffer.zip buffer.h buffer.cpp bufferlist.cpp bufferlist.h

val:
	valgrind --leak-check=full ./driver.out