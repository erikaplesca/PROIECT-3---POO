#ifndef MASINA_FACTORY_H
#define MASINA_FACTORY_H

#include "masina.h"
#include "client.h"
#include <string>

class MasinaClientFactory {
public:
    static Masina<Client> create(const std::string& nr, const std::string& marca, const std::string& model, const Client& proprietar) {
        return Masina<Client>(nr, marca, model, proprietar);
    }
};

#endif // MASINA_FACTORY_H
