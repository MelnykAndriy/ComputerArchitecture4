//
// Created by mandriy on 5/10/15.
//


#include "../socket/TCPSocket.h"
#include "../connection/connection.h"
#include <boost/serialization/vector.hpp>

using namespace std;


int main(int argc, char *argv[]) {

    OutTCPSocket out("localhost", 4242);

    vector<int> vector_to_sort;
    for (int i = 0; i < 20000; i++) {
        vector_to_sort.push_back(i);
    }
    serializedWrite(out, vector_to_sort);

    return 0;
}