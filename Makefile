#####################################################
#
#	Author: William Posey
#	Course: COP5536	
#	Makefile for HashtagCounter
#	
#####################################################
FLAGS	= -std=c++11 -g -Wall -Wno-unused-variable -Wno-unused-function -Wno-sign-compare
LINK	= -pthread
SRC	= ($wildcard *.cpp)
OBJ	= $(SRC:.cpp=.o)
TARGET	= hashtagcounter

all	: $(TARGET)

$(TARGET): $(OBJ)
	g++ $(LINK) $(FLAGS) -o $@ $(OBJ)
			
.cpp.o	:
	g++ $(FLAGS) -c $< -o $@

.PHONY	: clean

clean 	: 
	rm -f *.o $(TARGET)
