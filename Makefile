CPPFLAGS=-std=c++11

pnt: pnt_example.o
	$(CXX) -o pnt pnt_example.o
clean:
	rm -f pnt pnt_example.o
