CFLAGS  = -std=c++11
CC = g++


# Since the blah target is first, it is the default target and will be run when we run "make"

ILWSLogger.o: ILWSLogger.cpp 
	mkdir -p objFiles/
	echo hello1
	$(CC) -c $(CFLAGS) $?  -o objFiles/$@

Registery.o: LogRegistery.cpp  LogRegistery.hpp  ILWSLogger.o
	mkdir -p objFiles/
	echo hello2
	$(CC) -c $(CFLAGS) LogRegistery.cpp  -o objFiles/$@

SimpleLogger.o: Registery.o SimpleLogger.hpp SimpleLogger.cpp
	echo hello 2.5
	$(CC) -c $(CFLAGS) SimpleLogger.cpp -o objFiles/$@

SimpleLoggerTest: SimpleLogger.o
	mkdir -p Executables/
	mkdir -p objFiles/
	echo hello3
	$(CC) -c $(CFLAGS) simpleLoggerTest.cpp -o objFiles/simpleLoggerTest.o
	$(CC) $(CFLAGS)  objFiles/simpleLoggerTest.o objFiles/SimpleLogger.o objFiles/Registery.o objFiles/ILWSLogger.o  -o Executables/$@


clean:
	rm -f objFiles/* Executables/*