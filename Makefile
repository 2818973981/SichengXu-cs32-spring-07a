# Makefile for lab07a test

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

OBJS = lab07atest.o WordCount.o tddFuncs.o
TARGET = lab07atest

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

lab07atest.o: lab07atest.cpp WordCount.h tddFuncs.h
	$(CXX) $(CXXFLAGS) -c lab07atest.cpp

WordCount.o: WordCount.cpp WordCount.h
	$(CXX) $(CXXFLAGS) -c WordCount.cpp

tddFuncs.o: tddFuncs.cpp tddFuncs.h
	$(CXX) $(CXXFLAGS) -c tddFuncs.cpp

clean:
	rm -f *.o $(TARGET)
