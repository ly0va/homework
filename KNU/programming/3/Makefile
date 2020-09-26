main : main.o fib.o loops.o
	g++ -o $@ $^

fib.o : fib.?pp 

main.o : main.cpp loops.hpp

loops.o : loops.?pp fib.hpp

clean : 
	rm *.o main index.html
