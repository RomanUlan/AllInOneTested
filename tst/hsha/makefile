#######################################################
#######################################################
#######################################################
##########                                   ##########
########## Author:  Roman Ulan               ##########
########## Mail:    roman.ulan@gmail.com     ##########
##########                                   ##########
#######################################################
#######################################################
#######################################################

#######################################################
##########        BEGIN User part            ##########
##########       You can change it           ##########
#######################################################
CFLAGS = -std=c++11 -Wall -g -I ../mocks -I ../.. \
		 -I ../../IO -I ../../EchoResponder \
		 -I ../../EchoResponder/EventDemultiplexer \
		 -I ../../EchoResponder/EventSources
LDFLAGS = -lgtest -lgmock -lgmock_main -lpthread
SOURCES = ../../IO/Epoll.cpp \
		  ../../IO/Socket.cpp \
		  ../../IO/TcpSocket.cpp \
		  ../../Threading/ThreadPool.cpp \
		  ../../EventEngines/EventDemultiplexer.cpp \
		  ../../EventEngines/EventSource.cpp \
		  ../../EchoResponder/EventDemultiplexer/EpollED.cpp \
		  ../../EchoResponder/EventSources/SocketES.cpp \
		  ../../EchoResponder/EventSources/ListenerES.cpp \
		  ../../EchoResponder/EventSources/MessageES.cpp \
		  ../../EchoResponder/EventHandlers/AcceptorSEH.cpp \
		  ../../EchoResponder/EventHandlers/EchoResponderAEH.cpp \
		  ../../EchoResponder/EventHandlers/EchoResponderSEH.cpp \
		  ../mocks/EpollMock.cpp \
		  ../mocks/TcpSocketMock.cpp \
		  HsHaTests.cpp
NAME = prog
#######################################################
##########        END User part              ##########
#######################################################

#######################################################
##########      BEGIN Automation part        ##########
##########     You shouldn't change it       ##########
#######################################################
OBJECTS = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(NAME)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(NAME)
#######################################################
##########       END Automation part         ##########
#######################################################

