#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>

class Angajat
{
private:
    std::string m_numeAngajat;
    int m_statiaLucru;

public:
    Angajat();
    Angajat(const std::string& m_numeAngajat, const int& m_statiaLucru);
    ~Angajat();

    Angajat(const Angajat& angajat);
    Angajat& operator=(const Angajat& angajat);

    std::string getNume() const;
    int getStatiaLucru() const;

    void setNume(const std::string& m_numeAngajat);
    void setStatiaLucru(const int& m_statiaLucru);

    friend std::ostream& operator<<(std::ostream& os, const Angajat& angajat);
    friend std::istream& operator>>(std::istream& is, Angajat& angajat);
};

#endif //ANGAJAT_H
