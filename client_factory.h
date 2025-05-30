#ifndef CLIENT_FACTORY_H
#define CLIENT_FACTORY_H

#include "client.h"
#include <string>

class ClientFactory {
public:
    static Client create(const std::string& nume, const std::string& tipClient) {
        return Client(nume, tipClient);
    }
};

#endif // CLIENT_FACTORY_H
