# Compiler is G++
CXX = g++


#MUDLib directory
MUDLIBDIR = ../../../Libraries
SOCKETLIBDIR = $(MUDLIBDIR)/SocketLib
THREADLIBDIR = $(MUDLIBDIR)/ThreadLib
BASICLIBDIR  = $(MUDLIBDIR)/BasicLib

# libraries
LIBS = -lpthread -ldl -lutil

# flags
CFLAGS = -I$(MUDLIBDIR)

link: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(THREADLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(SOCKETLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(BASICLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) *.cpp *.o
