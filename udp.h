#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <list>

#define BUFFERSIZE 2*4096

// Fonctions utiles
void wait( float seconds ) { usleep( (int) ( seconds * 1000000.0f ) ); }



// Package struct
struct UdpPackage {
    
    char msg[BUFFERSIZE]; // data or message à transmettre
    uint id; //identifiant du paquet
    uint ac_reception; //Accusé de reception
    float time; //time offset depuis qu'il a était envoyé ou recu
    int len; // taille du packet en bytes
    
};

// Class queue pour sauvegarde

class UdpPacketList : public std::list<UdpPackage> {
    
    // Methodes
    public:
    
        // Fonction d'affichage
        void displayElement(){
            if(empty()){
                std::cout << "Empty list !" << std::endl;
            }else{
                for(UdpPacketList::iterator it = begin(); it != end(); it++){
                    std::cout << "id : " << it->id << ", " << "len : " <<
                        it->len << std::endl;
                }   
            }
            
        }
        
        // Savoir si un packet est dans la list
        bool isHere(uint id) {
            for(iterator it = begin(); it != end(); it++){
                if(it->id == id){
                    return true;
                }
            }
            return false;
        }
        
        // Ajout packet dans l'ordre croissant des id
        void insertUdpPacket(const UdpPackage &up){
            
            // Si la liste est vide, ajout
            if(empty()){
                push_front(up);
            }else{
                // Sinon on analyse le dernier élément
                if(up.id > back().id){
                    push_back(up);
                    // Sinon on analyse le premier élément
                }else if (front().id > up.id) {
                    push_front(up);
                    // Sinon on parcourt la liste
                } else{
                    for(UdpPacketList::iterator it = begin(); it != end(); it++){
                        if(it->id > up.id){
                            insert(it, up);
                            break;
                        }
                    }
                }
            
            }
        }
};

// Fiabilisation du systeme

class ReliableUdp {
    
    //Methodes
    public:
        
        void SendPacket(int size){
            
            //Si id locale prise
            if(sendPacket_.isHere(localId_)){
                std::cout << "local id exists : " << localId_ << std::endl;
                sendPacket_.displayElement();
            }
            
            //Sinon creation package
            UdpPackage data;
            data.id = localId_;
            data.time = 0;
            data.len = size;
            
            //On met ce nouveau paquet en queue de list d'envoi
            sendPacket_.push_back(data);
        }
        
    //Attributs
    private:
        
        uint localId_;
        
        UdpPacketList sendPacket_; // list de paquet envoyé
};