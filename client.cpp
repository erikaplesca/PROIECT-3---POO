#include "client.h"
#include <iostream>


// ------- CONSTRUCTOR IMPLICIT PENTRU CLASA "Client"  -------

Client::Client()
{
    m_nume = "-";
    m_tipClient = "Nu se stie.";
}


// ------- CONSTRUCTOR DE INITIALIZARE
// CU PARAMETRI PENTRU CLASA "Client"  -------

Client::Client(const std::string& m_nume,
            const std::string& m_tipClient)
{
    this->m_nume = m_nume;
    this->m_tipClient = m_tipClient;
}


// ------- DESTRUCTORUL PENTRU CLASA "Client"  -------

Client::~Client() {}


// ------- CONSTRUCTOR DE COPIERE PENTRU CLASA "Client"  -------

Client::Client(const Client& other)
{
    this->m_nume = other.m_nume;
    this->m_tipClient = other.m_tipClient;
}


// ------- CONSTRUCTORUL DE COPIERE PRIN OPERATORUL "="  -------

Client& Client::operator=(const Client& other)
{
    if (this != &other) 
    {
        this->m_nume = other.m_nume;
        this->m_tipClient = other.m_tipClient;
    }
    return *this;
}


// ------- GETTER-ELE PENTRU CLASA "CLIENT"  -------
std::string Client::getNume() const
{
    return m_nume;
}
std::string Client::getTipClient() const
{
    return m_tipClient;
}


// ------- SETTER-ELE PENTRU CLASA "CLIENT"  -------

void Client::setNume(const std::string& m_nume)
{
    this->m_nume = m_nume;
}
void Client::setTipClient(const std::string& m_tipClient)
{
    this->m_tipClient = m_tipClient;
}


// ------- SUPRAINCARCARE DE OPERATORI ">>" SI "<<"
// (CITIRE SI AFISARE) -------

std::istream& operator>>(std::istream& is, Client& client)
{
    std::string nume, tipClient;
    is>>nume>>tipClient;
    client.setNume(nume);
    client.setTipClient(tipClient);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
    os << "Numele clientului: "
        << client.getNume()
        << "\nTipul clientului: "
        << client.getTipClient() <<'\n';
    return os;
}
