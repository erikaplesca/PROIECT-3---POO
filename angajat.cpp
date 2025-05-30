#include "angajat.h"
#include <iostream>

// ------- CONSTRUCTOR IMPLICIT PENTRU CLASA "Angajat"  -------

Angajat::Angajat()
{
    m_numeAngajat = "-";
    m_statiaLucru= 0;
}


// ------- CONSTRUCTOR DE INITIALIZARE
// CU PARAMETRI PENTRU CLASA "Angajat"  -------

Angajat::Angajat(const std::string& m_numeAngajat, const int& m_statiaLucru)
{
    this -> m_numeAngajat = m_numeAngajat;
    this -> m_statiaLucru = m_statiaLucru;
}


// ------- DESTRUCTORUL PENTRU CLASA "Angajat"  -------

Angajat::~Angajat() {}


// ------- CONSTRUCTOR DE COPIERE PENTRU CLASA "Angajat"  -------

Angajat::Angajat(const Angajat& other)
{
    this->m_numeAngajat = other.m_numeAngajat;
    this->m_statiaLucru= other.m_statiaLucru;
}


// ------- CONSTRUCTORUL DE COPIERE PRIN OPERATORUL "="  -------

Angajat& Angajat::operator=(const Angajat& other)
{
    if (this != &other) {
        this->m_numeAngajat = other.m_numeAngajat;
        this->m_statiaLucru= other.m_statiaLucru;
    }
    return *this;
}


// ------- GETTER-ELE PENTRU CLASA "Angajat"  -------

std::string Angajat::getNume() const
{
    return m_numeAngajat;
}
int Angajat::getStatiaLucru() const
{
    return m_statiaLucru;
}


// ------- SETTER-ELE PENTRU CLASA "Client"  -------
void Angajat::setNume(const std::string& m_numeAngajat)
{
    this -> m_numeAngajat = m_numeAngajat;
}
void Angajat::setStatiaLucru(const int& statiaLucru) {
    this->m_statiaLucru = statiaLucru; 
}



// ------- SUPRAINCARCARE DE OPERATORI ">>" SI "<<"
// (CITIRE SI AFISARE) -------

std::istream& operator>>(std::istream& is, Angajat& m_angajat)
{
    std::string m_nume_angajat;
    int m_statiaLucru;
    is>>m_nume_angajat>>m_statiaLucru;
    m_angajat.setNume(m_nume_angajat);
    m_angajat.setStatiaLucru(m_statiaLucru);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Angajat& m_angajat)
{
    os << "Nume angajat: " << m_angajat.getNume() << "\n"
    << "Statia de lucru: " << m_angajat.getStatiaLucru() <<'\n';
    return os;
}