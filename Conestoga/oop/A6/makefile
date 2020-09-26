TARGET=assign6

$(TARGET) : AmFmRadio.o PioneerCarRadio.o ultimateRadio.o
	g++ -o $@ $^

%.o : %.cpp *.h
	g++ -g -Wall -c -o $@ $<

$(TARGET).zip : *.cpp *.h
	zip $@ $^

clean :
	rm -f $(TARGET) *.o
