CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -lrt

OBJS =		messagehandler.o\
    main.o

LIBS =

TARGET =	client

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -lrt

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

