# Compiler is G++
CXX = g++

#MUDLib directory
MUDLIBDIR = ../../../Libraries
SOCKETLIBDIR = $(MUDLIBDIR)/SocketLib
THREADLIBDIR = $(MUDLIBDIR)/ThreadLib
BASICLIBDIR  = $(MUDLIBDIR)/BasicLib
SIMPLEMUDDIR = ./SimpleMUD

# libraries
LIBS = -lpthread

# flags
CFLAGS = -I$(MUDLIBDIR)


link: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(SOCKETLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(THREADLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(BASICLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) *.cpp -c;
	$(CXX) $(CFLAGS) $(SIMPLEMUDDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) *.o $(LIBS)
