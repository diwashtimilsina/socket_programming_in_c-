#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
  
using namespace std; 
  
int main() 
{ 
    //CREATING SOCKET
 int nSocket = socket(AF_INET, SOCK_STREAM, 0);
 if(nSocket==-1){
std:: cout<<"SOCKET NOT CREATED";
 }

 //SPECIFYING THE ADDRESS
sockaddr_in server;
server.sin_family = AF_INET;
server.sin_port  = htons(9909);
//The htons() function translates a short integer from host byte order to network byte order.
server.sin_addr.s_addr = INADDR_ANY;


//binding the socket to local port
int nRet=0;
nRet=bind(nSocket, (struct sockaddr*)&server , sizeof(server));
if(nRet<0){
	std :: cout<<"failed to bind"<<nRet;
	exit(0);
}
else{
	std ::cout<<"sucessfully binded to port : 9909";
	std::cout<<"\n";
}
 

//listen to new request;
nRet = listen(nSocket,5);
if(nRet<0){
	std :: cout<<"failed to listen"<<nRet;
	exit(0);
}
else{
	std ::cout<<"sucessfully started tolisten to port : 9909";
}

int client = accept(nSocket,nullptr ,nullptr); 
if(client<0){

std::cout<<"threw a Error";
}
 char buffer[1024] = { 0 }; 
    recv(client, buffer, sizeof(buffer), 0); 
    cout << "Message from client: " << buffer 
              << endl; 
  
    // closing the socket. 
    close(nSocket); 


    return 0; 
}