CPPFLAGS=-std=c++11

pnt: pnt_example.o ownship.o
	$(CXX) -o $@ $^
clean:
	rm -f pnt pnt_example.o
