#include <iostream>
#include <WinSock2.h>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

#define MAX 500

int main(int argc, char const *argv[])
{
    //init socket variables
    WSADATA WSAData;
    SOCKET server = INVALID_SOCKET;
    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("192.168.1.206");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    char MsgRecv[MAX];
	char MsgSend[MAX];
   
    //Initializing Winsock
    int iResult = WSAStartup(MAKEWORD(2,0), &WSAData);
    if (iResult != 0) {
        cout << "WSAStartup failed with error: " << iResult << endl;
        return 1;
    }

    //creating a client side socket 
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        closesocket(server);
        WSACleanup();
        return 1;
    }

    //connecting the client side socket
    iResult = connect(server, (SOCKADDR*)&addr, sizeof(addr));
    if (iResult == SOCKET_ERROR) {
        closesocket(server);
        WSACleanup();
        cout << "Socket closed." << endl;
        return 1;
    }
    else cout << "Connected to server!\n\n" << endl;

    //Dialog between server and client
    while(true){
        cout << "Client : ";
        //sending message
        cin.getline(MsgSend, MAX);
        iResult = send(server, MsgSend, strlen(MsgSend)+1, 0);
        if (iResult == SOCKET_ERROR){
            cout << "send failed with error: " << WSAGetLastError() << endl;
            closesocket(server);
            WSACleanup();
            return 1;
        }
        else{    
            if(MsgSend[0] == 'b' && MsgSend[1] == 'y' && MsgSend[2] == 'e'){
                cout << "\nConnection ended...\n" ;
                break;
            }
        }
        //receiving message
        iResult = recv(server, MsgRecv , MAX , 0);
        if (iResult < 0) {
            cout << "recv failed with error: " << WSAGetLastError() << endl;
            closesocket(server);
            WSACleanup();
            return 1;
        }
        else if(iResult == 0) 
            cout << "\nConnection ended...\n" ;
        else{
            cout << "received server : " << MsgRecv <<endl;
            if(MsgRecv[0] == 'b' && MsgRecv[1] == 'y' && MsgRecv[2] == 'e')
            {
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