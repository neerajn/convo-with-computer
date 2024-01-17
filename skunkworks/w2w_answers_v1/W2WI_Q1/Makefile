CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -lpthread -lrt

OBJS =		ThreadData.o\
    SolutionQ1.o\
    W2WI_Q1.o\

LIBS =

TARGET =	myprinter

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -lpthread -lrt

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
