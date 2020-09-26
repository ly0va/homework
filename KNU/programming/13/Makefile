
main : main.cpp generator.o spectre.o demo.o
	g++ -g -o $@ $^

spectre.o : spectre.cpp spectre.hpp
	g++ -g -c -o $@ $<

generator.o : generator.cpp generator.hpp
	g++ -g -c -o $@ $<

demo.o : demo.cpp demo.hpp
	g++ -g -c -o $@ $<

clean: 
	rm -f *.o main index.html
