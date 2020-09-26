assign1a : assign1.o assessGrade.o
	g++ -o assign1a assign1.o assessGrade.o

assign1b : unitTest.o assessGrade.o
	g++ -o assign1b unitTest.o assessGrade.o

%.o : %.cpp assessGrade.h

clean :
	rm -f assign1? *.o
