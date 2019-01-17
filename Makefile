CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++17
LDFLAGS=
VPATH=src

EXEC=cmkv
SRC=src/main.cpp

all: $(EXEC)

cmkv: main.o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
