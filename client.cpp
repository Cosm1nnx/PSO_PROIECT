#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void sendFile(int clientSocket) {
    std::cout<<"Care este numele fisierului: ";
    std::string filename;
    std::cin>>filename;
    char control[50]="upload";
     send(clientSocket,control,50,0);
     send(clientSocket,(void*)filename.size(),4,0);
    char buffer[BUFFER_SIZE];
    printf("trimit numele\n");

    send(clientSocket,filename.c_str(),filename.size(),0);
    std::cout<<"Deschid fisierul :"<<filename.c_str() <<std::endl;
    int fd=open(filename.c_str(),O_RDONLY);
    int bytesread;
    do 
    {
         bytesread=read(fd,buffer,sizeof(buffer));
          if(bytesread==0){

            break;
         }
         send(clientSocket,&bytesread,4,0);
        
        send(clientSocket, buffer, bytesread, 0);
    }while (bytesread!=0);
    
    std::cout << "File sent successfully." << std::endl;
    close(fd);
}

void receiveFile(int serverSocket) {
    std::cout<<"Care este numele fisierului: ";
    std::string filename;
    std::cin>>filename;
    char control[50]="Download";
    send(serverSocket,control,50,0);
    send(serverSocket,(void*)filename.size(),4,0);
    send(serverSocket,filename.c_str(),filename.size(),0);
    int fd=open(filename.c_str(),O_WRONLY | O_CREAT | O_TRUNC);

    if (fd<0) {
        std::cerr << "Error creating file." << std::endl;
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytesReceived;
    int dim;
    do {
       
        recv(serverSocket,&dim,4,0);
        if(dim==0)
        break;
        bytesReceived = recv(serverSocket, buffer, dim, 0);
        std::cout<<buffer<<std::endl;
        std::cout<<"Dimensiune trimisa:"<<dim<<std::endl;
        
        write(fd,buffer,bytesReceived);
        
    }while (bytesReceived!=0);
    

    std::cout << "File received successfully." << std::endl;
    close(fd);
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Socket creation failed." << std::endl;
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    
    serverAddr.sin_addr.s_addr = inet_addr("172.16.34.107");

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    while(1)
    {
        std::string instruciune;
        std::cin>>instruciune;
        if(instruciune=="exit")
        {
            break;
        }
        else if(instruciune=="download")
        {

            receiveFile(clientSocket);
        }
        else if (instruciune=="upload")
        {
            sendFile(clientSocket);
        }
        

    }
    close(clientSocket);
    std::cout<<"Clientul a fost inchis\n";
    return 0;
}