CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++17
LDFLAGS=
VPATH=src

EXEC=cmkv

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)

all: $(EXEC)

cmkv: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
