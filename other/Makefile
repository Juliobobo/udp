#
progs=udpclient udpserver

# for SunOS, comment SOLARISLIBS out
# for Solaris comment SOLARISLIBS in

#SOLARISLIBS= -lsocket -lnsl 

all: $(progs)

udpclient: udpclient.cpp
	g++ -std=c++11 $< -o $@

udpserver: udpserver.cpp
	g++ -std=c++11 $< -o $@

clean:
	rm $(progs)