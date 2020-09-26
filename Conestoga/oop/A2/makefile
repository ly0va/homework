assign2: testDisneyCharacter.o DisneyCharacter.o
	g++ -o assign2 $^

%.o : %.cpp DisneyCharacter.h
	g++ -g -Wall -c -o $@ $<

assign2.zip : *.cpp *.h
	zip assign2.zip $^

clean :
	rm -f assign2 *.o
