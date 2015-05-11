

#include <iostream>
#include "socket/TCPSocket.h"
#include "thread/myThread.h"
#include "connection/connection.h"

#include <boost/serialization/vector.hpp>
#include <boost/program_options.hpp>

using namespace std;
using namespace boost::program_options;
using namespace concurrent;

#define DEFAULT_PORT 4242
#define THREADING_FORK 1
#define THREADING_PTHREAD 2
#define THREADING_ASIO 3

#define THREADING THREADING_PTHREAD

int main(int argc, char *argv[]) {
    unsigned short port;

    options_description desc("Client options");
    desc.add_options()
            ("help,h", "produce help message")
            ("port,p", value<unsigned short>(&port)->default_value(DEFAULT_PORT), "server port");
    variables_map args;
    try {
        parsed_options parsed = command_line_parser(argc, argv).options(desc).run();
        store(parsed, args);
        notify(args);
    } catch(std::exception& ex) {
        cerr << desc << endl;
        exit(EXIT_FAILURE);
    }


    InTCPSocket server_socket(port);

    while (true) {
        auto new_socket = server_socket.accept_connection();

#if (THREADING == THREADING_FORK)
        if ( !fork() ) {
            vector<double> provided_vector = serializedRead< vector<double> >(*new_socket.get());
            sort(begin(provided_vector), end(provided_vector));
            serializedWrite(*new_socket.get(), provided_vector);
            break;
        }

#elif (THREADING == THREADING_PTHREAD)
        auto socket_ptr = new unique_ptr<TCPSocket>(std::move(new_socket));
        Thread task_thread([](void* socket)->void* {
            unique_ptr<TCPSocket>* data_socket = (unique_ptr<TCPSocket>*)socket;
            vector<double> provided_vector = serializedRead< vector<double> >(*(*data_socket).get());
            sort(begin(provided_vector), end(provided_vector));
            serializedWrite(*(*data_socket).get(), provided_vector);
            delete data_socket;
            return nullptr;
        }, socket_ptr);
        task_thread.deatch();

#elif (THREADING == THREADING_ASIO)

        // asio here


#endif



    }


    return 0;
}