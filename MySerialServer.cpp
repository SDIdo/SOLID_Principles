//
// Created by idox on 1/3/19.
//

#include "MySerialServer.h"
#include <thread>

struct Params{
    int port;
    ClientHandler* clientHandler;
};

void MySerialServer::open(int port, ClientHandler *clientHandler) {
    pthread_t threadID;

    Params inputsToRunSerialServer;
    inputsToRunSerialServer.clientHandler = clientHandler;
    inputsToRunSerialServer.port = port;

    pthread_create(&threadID, nullptr, runSerialServer, (void*)&inputsToRunSerialServer);
    cout << "main thread is old and dying...\n";
    pthread_join(threadID, nullptr);
}

/**
 * This method runs the server: reads information from client from
 * the socket, and updates samples map and symbol map accordingly.
 * @param a void pointer.
 * @return void pointer.
 */
void *MySerialServer::runSerialServerFunc(void *arguments) {
    struct Params *inputsToRunSerialServer = (Params*)arguments;
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    serv_addr.sin_port = htons(inputsToRunSerialServer->port);

    /* Now bind the host address using bind() call.*/
    if (bind(this->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    /* Now start listening for the clients, here process will
 * go in sleep mode and will wait for the incoming connection
 */

    cout << "Listening\n";
    listen(this->sockfd, 5);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    this->sockfd = accept(this->sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (this->sockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    cout << "Success\n";



    int n = 0;
    char buffer[256];
    bzero(buffer, 256);
    string information;


//    inputsToRunSerialServer->clientHandler->handleClient(cin, cout);









//
//    while (true) {
//        n = read(this->sockfd, buffer, 255);
//        if (n < 0) {
//            cout << "non valid read from user\n";
//            this->stop();
//            pthread_exit(arguments);
//        }
//        cout << "n is " << n << "\n";
//        information = string(buffer);
//        cout << "Here is info: " << information << endl;
//        string stringStream;
//        cout << "Whoo\n";
//        inputsToRunSerialServer->clientHandler->handleClient(information, stringStream);
//        cout << stringStream << "\n";
//        break;
//    }
}
/**
 * This method is used by the pthread to run the opened server.
 * @param a void pointer.
 * @return void pointer.
 */
void* MySerialServer::runSerialServer(void* a){
    return ((MySerialServer *) a)->runSerialServerFunc(a);
}



void MySerialServer::stop() {

}
void MySerialServer::start() {

}