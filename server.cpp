#include <iostream>
#include <WinSock2.h>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

#define MAX 500

int main(int argc, char const *argv[])
{
    //init socket variables
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    char MsgRecv[MAX];
	char MsgSend[MAX];
    int clientAddrSize = sizeof(clientAddr);

    //Initializing Winsock
    int iResult = WSAStartup(MAKEWORD(2,0), &WSAData);
    if (iResult != 0) {
        cout << "WSAStartup failed with error: " << iResult << endl;
        return 1;
    }

    //creating a server side socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        closesocket(server);
        WSACleanup();
        return 1;
    }

    //binding the server side socket
    iResult = bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
        if (iResult == SOCKET_ERROR) {
        cout << "bind failed with error: " << WSAGetLastError() << endl;
        closesocket(server);
        WSACleanup();
        return 1;
    }
    
    //listen to the client while others are waiting in queue of size 5
    iResult = listen(server, 5);
    if (iResult == SOCKET_ERROR) {
        cout << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(server);
        WSACleanup();
        return 1;
    }
    else cout << "Listening for incomming connections..." << endl;

    //accepting the client 
    client = accept(server, (SOCKADDR*)&clientAddr, &clientAddrSize);
    if (client == INVALID_SOCKET) {
        cout << "accept failed with error: " << WSAGetLastError() << endl;
        closesocket(server);
        WSACleanup();
        return 1;
    }
    else cout << "Server accepted the request. \n" << endl;

    //Dialog between server and client
    while(true){
        //receiving message
        iResult = recv(client, MsgRecv , MAX , 0);
        if (iResult < 0) {
            cout << "recv failed with error: " << WSAGetLastError() << endl;
            closesocket(client);
            WSACleanup();
            return 1;
        }
        else if(iResult == 0) 
            cout << "\nConnection ended...\n" ;
        else{
            cout << "received client : " << MsgRecv << endl;
            if(MsgRecv[0] == 'b' && MsgRecv[1] == 'y' && MsgRecv[2] == 'e')
            {
                cout << "\nConnection ended...\n" ;
                break;
            }
        }
        cout << "Server : ";
        //sending message
        cin.getline(MsgSend, MAX);
        iResult = send(client , MsgSend , strlen(MsgSend)+1 , 0);
        if (iResult == SOCKET_ERROR){
            cout << "send failed with error: " << WSAGetLastError() << endl;
            closesocket(client);
            WSACleanup();
            return 1;
        }
        else{
            if(MsgSend[0] == 'b' && MsgSend[1] == 'y' && MsgSend[2] == 'e'){
                cout << "\nConnection ended...\n" ;
                break;
            }
        }
    }

    closesocket(server);
    WSACleanup();
    cout << "Socket closed." << endl;
    return 0;
}