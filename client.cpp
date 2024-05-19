#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include<cstring>
  
  using std:: string;
using namespace std; 
  
int main() 
{ 
    //CREATING SOCKET
 int client = socket(AF_INET, SOCK_STREAM, 0);
 if(client==-1){
std:: cout<<"SOCKET NOT CREATED";
 }

//Adress specification
 sockaddr_in server;
 server.sin_family = AF_INET;
 server.sin_port = htons(9909);
 server.sin_addr.s_addr= INADDR_ANY;


//CONNECTION
 int nRet = connect(client ,(struct sockaddr*)&server,sizeof(server));
if(nRet<0){
	std::cout<< "connection not established";
}

//string message;
//sending data
//std::cout<<"Enter your messege";
//std::cin>>message;


const char* message = "Hello, server!"; 
    send(client, message, strlen(message), 0); 

    close(client); 
  
    return 0; 
}
