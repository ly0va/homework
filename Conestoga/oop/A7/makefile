TARGET=assign7

$(TARGET) : Circle.o Square.o Shape.o myShape.o
	g++ -o $@ $^

%.o : %.cpp *.h
	g++ -g -Wall -c -o $@ $<

html : *.cpp *.h doxyfile
	doxygen doxyfile

$(TARGET).zip : *.cpp *.h html
	zip -r html.zip html
	zip $@ *.cpp *.h html.zip
	zip -d $@ mainPage.h
	rm html.zip

clean : 
	rm *.o $(TARGET) html
