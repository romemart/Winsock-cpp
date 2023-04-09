## Client-Server side Chat

Socket programming is a way of connecting two nodes on a network to communicate with each other. One socket(node) listens on a particular port at an IP, while the other socket reaches out to the other to form a connection. The server forms the listener socket while the client reaches out to the server.

### Stages for server (server.cpp)
1. Socket creation:
2. Setsockopt:
3. Bind:
4. Listen:
5. Accept:
6. Read/Write communication:
7. Close:

### Stages for client (client.cpp)
1. Socket creation:
2. Socket conection:
3. Read/Write communication:
4. Close:

### Before compiling:

Set server ip address in line 16 of client.cpp
Run CMD and type 
```prompt
C:\Winsock> ipconfig
```
and then write the ip address en client.cpp
`addr.sin_addr.s_addr = inet_addr("192.168.1.206");` 

### Compiling:
Build using your preference IDE or type the following lines: 
```cpp
C:\Winsock>cl .\server.cpp
C:\Winsock>cl .\client.cpp
``` 

### Running
Starts a dialog between the server and the client when someone says "bye", the connection is immediately closed.

|Server side|Client side|
|---|---|
|`C:\Winsock> .\server.exe`|`C:\Winsock> .\client.exe`|
|`Listening for incomming connections...`|`Connected to server!`|
|`Server accepted the request.`||
|`received client : Hi`|`Client : Hi`|
|`Server : How are you?`|`received server : How are you?`|
|`received client : fine!!`|`Client : fine!!`|
|`Server : bye`|`received server : bye`|
|`Connection ended...`|`Connection ended...`|
|`Socket closed.`|`Socket closed.`|