all: server client test

%: %.cpp
	g++ -std=c++11 -g $< -o $@


client: client.cpp
	g++ -std=c++11 -g $< -o $@
	
server: server.cpp
	g++ -std=c++11 -g $< -o $@

struct: struct.cpp
	g++ -std=c++11 $< -o $@

test: test.cpp
	g++ -std=c++11 $< -o $@