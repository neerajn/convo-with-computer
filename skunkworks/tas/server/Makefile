CXXFLAGS =	-O2 -g -Wall -Wstrict-aliasing -fmessage-length=0 -lrt

OBJS =		commanddata.o\
    filetestoperationcommand.o\
    getdatecommand.o\
    nextnprimecommand.o\
    nextprimecommand.o\
    testprimecommand.o\
    messagehandler.o\
    main.o

LIBS =

TARGET =	server

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -lrt

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

