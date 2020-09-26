TARGET=assign5

$(TARGET): AmFmRadio.o PioneerCarRadio.o carDriver.o
	g++ -o $@ $^

%.o : %.cpp *.h
	g++ -g -Wall -c -o $@ $<

$(TARGET).zip : *.cpp *.h
	zip $@ $^

clean :
	rm -f $(TARGET) *.o
