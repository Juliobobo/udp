#include "udp_packet.h"

int main(int argc, char *argv[]) {
    
    int sock;
    int port;
    int n;
    int server_length;
    int seq_locale, seq_distant;
    struct sockaddr_in serveraddr;
    struct sockaddr_in client;
    struct hostent *server;
    char *hostname;
    char *hostaddr;
    char bufferReceive[BUFFERSIZE];
    char bufferSend[BUFFERSIZE];
    
    /* check command line arguments */
    if (argc != 3) {
        std::cerr << "Pas assez d'arguments !" << std::endl;
        exit(0);
    }
    
    hostname = argv[1];
    port = atoi(argv[2]);

    /* Ouverture socket */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0){ 
        std::cerr << "Erreur : socket non crée !" << std::endl;
    }
    
    /* on recupere le hostname DNS*/
    server = gethostbyname(hostname);
    if (server == NULL) {
        std::cerr << "Erreur: " << hostname << std::endl;
        exit(0);
    }

    /* Server adresse */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(port);
    
    hostaddr = inet_ntoa(serveraddr.sin_addr);
    
    //Recap
    std::cout << "-----------------------" << std::endl;
    std::cout << "<<<< Client create >>>>" << std::endl;
    std::cout << "          ---          " << std::endl;
    std::cout << "> Hostname : "  << hostname << ", "<< hostaddr << std::endl;
    std::cout << "> Port : "  << argv[2] << std::endl;
    std::cout << "-----------------------" << std::endl;


    udp_package *data_s = new udp_package;
    udp_package *data_r = new udp_package;
    
    server_length = sizeof(serveraddr);
    int size = sizeof(struct udp_package);
    
    int i = 0;
    seq_locale = 0;
    seq_distant = 0;
    
    // Loop
    while (1){ // Boucle qui envoi i message
        /*Treatment of data */
       
            // Mise à zero
            bzero(data_s, size);
            bzero(data_r, size);
        
        // boucle simulant les 10envoi/s       
        while(++i < 101){     
            strcpy(data_s->msg, "loop");  
            data_s->len = size;
            
            // A la creation d'un paquet
            data_s->id = seq_locale;
            data_s->ac_reception = seq_distant;
        
            //std::cout << "Entrer message :";
            //std::cin >> data_s->msg;
            
            /* Envoi message aux server */
            n = sendto(sock, data_s, data_s->len, 0, (struct sockaddr *)&serveraddr, server_length);
            //std::cout << "> n_sendto : "  << n << std::endl;
                
            if (n < 0){
                std::cerr << "Erreur: sendto !" << std::endl;
            }else{
                //Apres chaque envoi on incrémente seq_locale
                ++seq_locale;  
            } 
            
            std::cout << "-----------------" << std::endl;
            std::cout << "||||| Envoi |||||" << std::endl;
            std::cout << "-----------------" << std::endl;
            std::cout << "> Message : "  << data_s->msg << std::endl;
            std::cout << "> Length : "  << data_s->len << std::endl;
            std::cout << "> id : "  << data_s->id << std::endl;
            std::cout << "> ac_reception : "  << data_s->ac_reception << std::endl;
            std::cout << "> i : "  << i << std::endl;
               
        }
    
        /* Reponse du server */
        n = recvfrom(sock, data_r, size, 0, (struct sockaddr *)&serveraddr, (socklen_t*)&server_length);
        if (n < 0){
            std::cerr << "Erreur: recvfrom !" << std::endl;
        }else{
            //Reception paquet
            //Quand je recois un paquet maj de seq_distant
            ++seq_distant;
            if(data_r->id < seq_distant){
                seq_distant = data_r->id;
            }
        }
        
        std::cout << "---------------------" << std::endl;
        std::cout << "||||| Reception |||||" << std::endl;
        std::cout << "---------------------" << std::endl;
        //std::cout << "n : " << n << std::endl;
        std::cout << "Datagramme recu : " << data_r->msg << std::endl;
        std::cout << "id : " << data_r->id << std::endl;
        std::cout << "ac_reception : " << data_r->ac_reception << std::endl;
        std::cout << "seq_locale : " << seq_locale << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

    return 0;
}
