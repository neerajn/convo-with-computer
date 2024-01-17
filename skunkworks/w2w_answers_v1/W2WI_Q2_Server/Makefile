CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -lpthread -lrt

OBJS =		CommandData.o\
    AddCommand.o\
    MultCommand.o\
    SubtractCommand.o\
    XorCommand.o\
    PowCommand.o\
    ClientData.o\
    Job.o\
    Message.o\
    ThreadData.o\
    ThreadPool.o\
    JobWorkerContext.o\
    JobWorker.o\
    Connection.o\
    SolutionQ2Server.o\
    W2WI_Q2_Server.o

LIBS =

TARGET =	server

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -lpthread -lrt

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
