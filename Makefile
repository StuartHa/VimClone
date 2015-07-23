CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

CXX = clang++

OBJS =		main.o

LIBS = -lcurses

TARGET =	a.out

$(TARGET): main.cc editor.cc text.cc
	$(CXX) -O0 -std=c++11 -g -o $(TARGET) main.cc editor.cc text.cc $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
