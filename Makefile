CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = apuec_system

SRCS = main.cpp \
       shared/Player.cpp \
       shared/Stack.cpp \
       shared/HashMap.cpp \
       shared/Queue.cpp \
       shared/PriorityQueue.cpp \
       shared/CircularQueue.cpp \
       tasks/Task1_Scheduler.cpp \
       tasks/Task2_Registration.cpp \
       tasks/Task3_Spectator.cpp \
       tasks/Task4_Logger.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run