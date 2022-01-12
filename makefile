CXX = clang++
SRC = ./source
INCLUDE = -I ./include
STANDART = -std=c++11
DEBUGFLAGS = -Wall -g3 -O0


debug:
	clear
	$(CXX) $(STANDART) $(DEBUGFLAGS) $(SRC)/*.cpp -o ./bin/rstyletest $(INCLUDE) $(LIB)

clear:
	rm ./bin/def.log ./bin/engine
