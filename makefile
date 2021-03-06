CXX = clang++
SRC = ./source
INCLUDE = -I ./include
STANDART = -std=c++11
DEBUGFLAGS = -Wall -g3 -O0


debug:
	$(CXX) $(STANDART) $(DEBUGFLAGS) $(SRC)/*.cpp -o ./bin/rstyletest $(INCLUDE) $(LIB)
