# Compiler is G++
CXX = g++

# libraries
LIBS = -lpthread -ldl -lutil
PYTHONDIR = /usr/include/python2.2

# flags
CFLAGS = -I$(PYTHONDIR) -Xlinker -export-dynamic


link: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) *.cpp /usr/lib/python2.2/config/libpython2.2.a $(LIBS)
