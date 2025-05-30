#ifndef REPARATIE_H
#define REPARATIE_H

#include "masina.h"
#include "angajat.h"
#include "serviciu.h"
#include "client.h"

#include <memory>
#include <string>
#include <iostream>

class Reparatie {
private:
    Masina<Client> m_masina;
    Angajat m_angajat;
    std::shared_ptr<Serviciu> m_serviciu;

public:
    Reparatie();
    Reparatie(const Masina<Client>& masina, const Angajat& angajat, std::shared_ptr<Serviciu> serviciu);
    Reparatie(const Reparatie& other);
    Reparatie& operator=(const Reparatie& other);
    ~Reparatie();

    // Getters
    Masina<Client> getMasina() const;
    Angajat getAngajat() const;
    std::shared_ptr<Serviciu> getServiciu() const;
    std::string getTipReparatie() const;
    float getCost() const;

    // Setters
    void setMasina(const Masina<Client>& masina);
    void setAngajat(const Angajat& angajat);
    void setServiciu(std::shared_ptr<Serviciu> serviciu);

    void setAngajatStatieLucru(int statieLucru);

    // Operatorii de flux
    friend std::istream& operator>>(std::istream& is, Reparatie& reparatie);
    friend std::ostream& operator<<(std::ostream& os, const Reparatie& reparatie);

    static void interschimbareStatieLucru(Reparatie& r1, Reparatie& r2);
};

#endif // REPARATIE_H
