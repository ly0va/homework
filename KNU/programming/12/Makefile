.PHONY: all clean libs

BINARIES = spectre_main spectre_demo spectre_output
LIBS     = liboutput.a libspectre.a

all : $(BINARIES)

libs : $(LIBS)

spectre_demo : spectre_demo.cpp demo.o $(LIBS)
	g++ -o $@ $^

demo.o : demo.cpp demo.hpp
	g++ -c -o $@ $<

spectre_main : spectre_main.cpp libspectre.a
	g++ -o $@ $^

libspectre.o : libspectre.cpp libspectre.hpp
	g++ -c -o $@ $<

libspectre.a : libspectre.o
	ar rcs $@ $<

liboutput.o : liboutput.cpp liboutput.hpp
	g++ -c -o $@ $<

liboutput.a : liboutput.o
	ar rcs $@ $<

spectre_output : spectre_output.cpp $(LIBS)
	g++ -o $@ $^

clean :
	rm -f *.o *.html $(LIBS) $(BINARIES)
