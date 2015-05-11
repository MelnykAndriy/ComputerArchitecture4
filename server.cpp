

#include <iostream>
#include "socket/TCPSocket.h"
#include <boost/serialization/vector.hpp>
#include "connection/connection.h"

#define SERVER_PORT 4242

using namespace std;
//using namespace concurrent;



int main() {


    {
        InTCPSocket server_socket(SERVER_PORT);
        auto new_socket = server_socket.accept_connection();
        vector<int> provided_vector = serializedRead< vector<int> >(*new_socket.get());

        cout << "provided_vector " << provided_vector.size() << endl;
//        for (int &el: provided_vector)
//            cout << el << " ";
            cout << provided_vector[provided_vector.size() - 1] << " ";
        cout << endl;
        new_socket.get()->writeData("I got your message", 18);
    }

    return 0;
}