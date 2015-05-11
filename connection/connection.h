//
// Created by mandriy on 5/11/15.
//

#ifndef COMPUTERARCHITECTURE4_CONNECTION_H
#define COMPUTERARCHITECTURE4_CONNECTION_H

#include "../socket/TCPSocket.h"

#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <string.h>
#include <boost/archive/text_iarchive.hpp>

template <class WriteEntity>
void serializedWrite(TCPSocket& writeSocket, const WriteEntity& entity) {
    ostringstream serialize_stream;
    boost::archive::text_oarchive serializer(serialize_stream);
    serializer << entity;
    writeSocket.writeData(serialize_stream.str().c_str(), strlen(serialize_stream.str().c_str()) * sizeof(char));
}

template <class ReadEntity>
ReadEntity serializedRead(TCPSocket& readSocket) {
    char* buffer = new char[256];
    ReadEntity entity;
    string data;
    ssize_t number_of_bytes_read;
    do {
        memset(buffer, 0, 256);
        number_of_bytes_read = readSocket.readData(buffer, 255);
        data += buffer;
    } while ( number_of_bytes_read == 255 );
    istringstream serializable_stream(data.c_str());
    boost::archive::text_iarchive in(serializable_stream);
    in >> entity;
    delete[] buffer;
    return entity;
}


#endif //COMPUTERARCHITECTURE4_CONNECTION_H
