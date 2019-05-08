CC := g++
RM := del 
LIBS =
TARGET = CacheSimulator
OBJS = CacheSimulator.o Hit.o HelperTools.o

all:$(TARGET)
    

clean: 
	$(RM)  *.exe *.o
    
CacheSimulator: ${OBJS}
	$(CC)  -o CacheSimulator ${OBJS} -Wall

CacheSimulator.o: CacheSimulator.h base.h
	$(CC) -c CacheSimulator.c -Wall
	
Hit.o: Hit.h base.h
	$(CC) -c Hit.c -Wall
	
HelperTools.o: HelperTools.h base.h
	$(CC)  -c HelperTools.c -Wall