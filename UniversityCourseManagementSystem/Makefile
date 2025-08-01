#
# Makefile
# University Course Management System
#
# Created by Violet Chaffee on 8/1/25.
#

CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = university_system
SOURCES = main.cpp Student.cpp Course.cpp UniversitySystem.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)
	
clean:
	rm -f $(TARGET)
	
run: $(TARGET)
	./$(TARGET)
	
.PHONY: clean run
