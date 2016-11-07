#include "udp.h"

int main(int argc, char *argv[]){
    
    int sock; //le socket
    int server_length; // Taille adresse server
    int client_length; // Taille adresse client
    int n; //taille message
    int seq_locale, seq_distant;
    struct sockaddr_in server; // adresse serveur
    struct sockaddr_in client; // adresse client
    //char bufferSend[BUFFERSIZE]; // Tampon contenant les données envoyées
    char bufferReceive[BUFFERSIZE];
    char *hostaddr; // addr du client
    struct hostent *hostclient; // Info client host
    
    std::cout << "<<<< Server side >>>>" << std::endl;

    //On regarde si en entrée on a bien les bon argument
    if(argc != 2){
        std::cerr << "| Pas assez d'arguments |" << std::endl;
        exit(1);
    }
    
    //ouverture d'une socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        std::cerr << "Erreur : socket non crée !" << std::endl;
    }
    
    // Lie la socket à une ip et un port d'écoute
    server_length = sizeof(server); 
    bzero(&server, server_length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1])); 
    
    //Check du port d'écoute
    if(bind(sock, (struct sockaddr *)&server, server_length) < 0){
        std::cerr << "Erreur : Port non écouté !" << std::endl;
    }
    
    //Recap
    std::cout << "-----------------------" << std::endl;
    std::cout << "<<<< Server created >>>>" << std::endl;
    std::cout << "          ---          " << std::endl;
    std::cout << "> Port : "  << argv[1] << std::endl;
    std::cout << "-----------------------" << std::endl;
    
    UdpPackage *data_s = new UdpPackage;
    UdpPackage *data_r = new UdpPackage;
    
    seq_locale = 0;
    seq_distant = 0;

    //Boucle principale : ecoute 
    client_length = sizeof(client);
    int size = sizeof(struct UdpPackage);
    while(1){
        bzero(data_r , size);
        bzero(data_s , size);
        
        //recvfrom: reception du datagramme d'un client par UDP
        n = recvfrom(sock, data_r, size, 0, (struct sockaddr *)&client, (socklen_t*)&client_length);
        
        
        //Si on recoi rien message d'erreur
        if(n < 0){
            std::cerr<< "Erreur : Pas de récepetion !" << std::endl;
        }//else{
            //Reception paquet
            //Quand je recois un paquet maj de seq_distant
            /*++seq_distant;
            if(data_r->id < seq_distant){
                seq_distant = data_r->id;
            }*/
            
            //std::cout << "size : " << n << std::endl;
            //std::cout << "Datagramme recu : " << data_r->msg << std::endl;
          //  std::cout << "id : " << data_r->id << std::endl;
        //    std::cout << "len : " << data_r->len << std::endl;
        //}
        
        std::cout << "---------------------" << std::endl;
        std::cout << "||||| Reception |||||" << std::endl;
        std::cout << "---------------------" << std::endl;
        //std::cout << "n : " << n << std::endl;
        std::cout << "Datagramme  recu : " << data_r->msg << std::endl;
        std::cout << "id : " << data_r->id << std::endl;
        std::cout << "ac_reception : " << data_r->ac_reception << std::endl;
        std::cout << "seq_locale : " << seq_locale << std::endl;
        
        //On determine qui envoi le datagramme
        hostclient = gethostbyaddr((const char *)&client.sin_addr.s_addr, sizeof(client.sin_addr.s_addr), AF_INET);
        if (hostclient == NULL){
            std::cerr << "Erreur : gethostbyaddr !" << std::endl;
        }

        hostaddr = inet_ntoa(client.sin_addr);
        
        if (hostaddr == NULL){
            std::cerr<< "Erreur : inet_ntoa !" << std::endl;
        }
        
        std::cout << "Datagramme recu de : " << hostclient->h_name << ", " << hostaddr << std::endl;
        
        //wait(10);
        
        strcpy(data_s->msg, "acquittement");
        data_s->len = size;
        
        // A la creation d'un paquet
        data_s->id = seq_locale;
        data_s->ac_reception = seq_distant;
        
        //sento : envoi d'un message au client
        n = sendto(sock, data_s, data_s->len, 0, (struct sockaddr *) &client, client_length);
        
        if(n < 0){
            std::cerr << "Erreur: sendto !" << std::endl;
        }//else{
            //std::cout << "Accusé de reception !" << std::endl;
            //Apres chaque envoi on incrémente seq_locale
          //  ++seq_locale; 
        //}
        
        std::cout << "-----------------" << std::endl;
        std::cout << "||||| Envoi |||||" << std::endl;
        std::cout << "-----------------" << std::endl;
        std::cout << "> Message : "  << data_s->msg << std::endl;
        std::cout << "> Length : "  << data_s->len << std::endl;
        std::cout << "> id : "  << data_s->id << std::endl;
        std::cout << "> ac_reception : "  << data_s->ac_reception << std::endl;
        
        std::cout << "-----------------------" << std::endl;
    }
}