CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -lpthread -lrt

OBJS =		Client.o\
    SolutionQ2Client.o\
    W2WI_Q2_Client.o

LIBS =

TARGET =	client

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)  -lpthread -lrt

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
