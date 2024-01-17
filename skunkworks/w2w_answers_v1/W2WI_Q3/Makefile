CXXFLAGS =	-O2 -g -Wall -fmessage-length=0  -lpthread -lrt

OBJS =		SolutionQ3.o\
    W2WI_Q3.o

LIBS =

TARGET =	W2WI_Q3

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)  -lpthread -lrt

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
