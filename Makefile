CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++17 -O0 -g3
LDFLAGS=
VPATH=src

EXEC=cmkv

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(EXEC)

cmkv: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)

clean:
	rm -rf $(OBJS)

mrproper: clean
	rm -rf $(EXEC)
