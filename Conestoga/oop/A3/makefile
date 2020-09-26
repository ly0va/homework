assign3: AmFmRadio.o driver.o
	g++ -o assign3 $^

%.o : %.cpp AmFmRadio.h
	g++ -g -Wall -c -o $@ $<

assign3.zip : *.cpp *.h
	zip assign3.zip $^

clean :
	rm -f assign3 *.o
