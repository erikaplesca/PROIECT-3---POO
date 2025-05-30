#ifndef SERVICEEXCEPTION_H
#define SERVICEEXCEPTION_H

#include <exception>
#include <string>

class ServiceException : public std::exception {
protected:
    std::string m_mesaj;
public:
    ServiceException(const std::string& mesaj) : m_mesaj(mesaj) {}
    const char* what() const noexcept override { return m_mesaj.c_str(); }
};

class TipServiciuInvalidException : public ServiceException {
public:
    TipServiciuInvalidException(const std::string& tip)
        : ServiceException("\n !!!!! \n Tipul de serviciu '" + tip + "' nu este valid.\n !!!!! \n ") {}
};

class DataInvalidaException : public ServiceException {
public:
    DataInvalidaException(const std::string& data)
        : ServiceException("\n !!!!! \n Data '" + data + "' nu este valida.\n !!!!! \n ") {}
};

class NumarFacturaDuplicatException : public ServiceException {
    public:
        NumarFacturaDuplicatException(int numar)
            : ServiceException("\n !!!!! \n Numarul de factura " + std::to_string(numar) + " a mai fost folosit!\n !!!!! \n ") {}
    };
    

class TipProprietarInvalidException : public ServiceException {
    public:
        TipProprietarInvalidException(const std::string& tip)
            : ServiceException("\n !!!!! \n Tipul de proprietar '" + tip + "' nu este valid. (Doar Persoana_fizica sau Persoana_juridica)\n !!!!! \n ") {}
    };
    

#endif // SERVICEEXCEPTION_H
