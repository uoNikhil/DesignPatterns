#include <iostream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <memory>
#include <queue>
#include <unordered_map>


/**
 * This is the Server side code
 * Run this code:
 * Then open another terminal and Run the Client Side code (Flywright_ConnectionClient.cpp)
 * 
*/


class Connection {
private:
    int socket;
    sockaddr_in address;

public:
    Connection(int socket, sockaddr_in address) : socket(socket), address(address) {}

    void send(const std::string& message) {
        ::send(socket, message.c_str(), message.size(), 0);
    }

    std::string receive() {
        char buffer[1024] = {0};
        long valread = read(socket, buffer, 1024);
        return std::string(buffer);
    }

    void close() {
        ::close(socket);
    }
};

class ConnectionPool {
private:
    std::queue<std::shared_ptr<Connection>> availableConnections;

public:
    std::shared_ptr<Connection> getConnection(int client_socket, sockaddr_in address) {
        if (!availableConnections.empty()) {
            auto conn = availableConnections.front();
            availableConnections.pop();
            return conn;
        }

        auto newConnection = std::make_shared<Connection>(client_socket, address);
        return newConnection;
    }

    void releaseConnection(std::shared_ptr<Connection> connection) {
        availableConnections.push(connection);
    }
};

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    ConnectionPool pool;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    auto connection = pool.getConnection(client_socket, address);
    
    std::string message = connection->receive();
    std::cout << "Client: " << message << std::endl;
    
    connection->send("Hello from server");
    
    connection->close();
    pool.releaseConnection(connection);
    
    close(server_fd);
    return 0;
}
