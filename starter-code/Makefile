CXX = gcc
CXXFLAGS = -g -pedantic

all: server client

server: server.c
	$(CXX) $(CXXFLAGS) server.c -o server

client: client.c
	$(CXX) $(CXXFLAGS) client.c -o client

clean:
	rm -rf client server *.dSYM

.PHONY: clean
