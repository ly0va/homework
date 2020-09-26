assign4 : Circle.o Square.o Shape.o myShape.o
	g++ -o $@ $^

%.o : %.cpp *.h
	g++ -g -Wall -c -o $@ $<

html : *.cpp *.h doxyfile
	doxygen doxyfile

assign4.zip : *.cpp *.h html
	zip -r html.zip html
	zip $@ *.cpp *.h html.zip
	zip -d $@ mainPage.h
	rm html.zip

clean : 
	rm *.o assign4
