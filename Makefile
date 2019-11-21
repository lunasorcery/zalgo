all: zalgo

zalgo: main.cpp
	$(CXX) main.cpp -std=c++17 -lstdc++ -o zalgo -Wall -Wextra -Wpedantic

install: zalgo Makefile
	cp zalgo /usr/local/bin/zalgo

clean:
	rm -f zalgo
