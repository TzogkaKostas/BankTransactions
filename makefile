mygraph: main.o  implem.o classes.h
	g++ main.o implem.o -o mygraph

main.o: main.cpp
	g++ -c main.cpp 

implem.o: implem.cpp
	g++ -c implem.cpp -std=c++0x

clean:
	rm  main.o implem.o mygraph