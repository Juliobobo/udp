#include <iostream>
#include "udp.h"

using namespace std;

void test_packet_list() {
    
    cout << "-----------------------" << endl; 
    cout << "-- test packet list --" << endl; 
    cout << "-----------------------" << endl; 

	UdpPacketList udpPacketList_;
	
    cout << " << Back >>" << endl; 
    
	for (int i = 0; i < 11; ++i){
		
		UdpPackage data;
		data.id = i;
		data.len = 100;
		udpPacketList_.insertUdpPacket(data);
	}
	
	if(udpPacketList_.isHere(3)){
		    cout << "Element is here !" << endl; 
	}
	
	udpPacketList_.displayElement();
	
	cout << " << Front >>" << endl; 
    udpPacketList_.clear();
	for (int i = 11; i > 0; --i){
		
		UdpPackage data;
		data.id = i;
		data.len = 100;
		udpPacketList_.insertUdpPacket(data);
	}
	
	udpPacketList_.displayElement();
	
	cout << " << Random >>" << endl; 
    udpPacketList_.clear();
	for (int i = 11; i > 0; --i){
		
		UdpPackage data;
		data.id = rand() % 100;
		data.len = 100;
		udpPacketList_.insertUdpPacket(data);
	}
	
	udpPacketList_.displayElement();
	
}









//------------------------------------------------------------------------------
int main( int argc, char * argv[] ) {
    
    test_packet_list();
	

	return 0;
}
