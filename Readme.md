The following scenarios of client-server socket model will be implemented in this repository.
1. Server writes a message, client reads it.
2. Client sends a message, server reads it, for 5 times.
3. use two clients to connect to server to send 1 message at a time, server should use select on the sockets.
4. use two clients to connect to server. server should start one thread for each client.