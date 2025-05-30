#ifndef FACTURA_H
#define FACTURA_H

#include "client.h"
#include "reparatie.h"
#include <string>
#include <iostream>
#include <vector>

class Factura {
private:
    Client m_clientCurent;
    std::vector<Reparatie> m_reparatii; // Vector de reparații
    std::string m_dataEmitere;
    int m_nrFactura;
    float m_total;
    float m_tva;
    bool m_platita;

public:
    // Constructor implicit
    Factura();
    
    // Constructor de initializare cu parametri
    Factura(const Client& clientCurent, 
            const std::vector<Reparatie>& reparatii,
            const std::string& dataEmitere = "01/01/2025",
            const int& nrFactura = 0,
            const float& tva = 19.0f,
            const bool& platita = false);
    
    // Destructor
    ~Factura();
    
    // Constructor de copiere
    Factura(const Factura& factura);
    
    // Constructor de copiere prin operatorul =
    Factura& operator=(const Factura& factura);
    
    // Getters
    Client getClient() const;
    std::vector<Reparatie> getReparatii() const;
    Reparatie getReparatie(int index) const;
    int getNumarReparatii() const;
    std::string getDataEmitere() const;
    int getNrFactura() const;
    float getTotal() const;
    float getTVA() const;
    bool getPlatita() const;
    
    // Setters
    void setClient(const Client& clientCurent);
    void setReparatii(const std::vector<Reparatie>& reparatii);
    void setDataEmitere(const std::string& dataEmitere);
    void setNrFactura(const int& nrFactura);
    void setTVA(const float& tva);
    void setPlatita(const bool& platita);
    
    // Metode pentru gestionarea reparațiilor
    void adaugaReparatie(const Reparatie& reparatie);
    void stergeReparatie(int index);
    void actualizeazaTotal();
    
    // Alte metode utile
    float calculeazaTotalCuTVA() const;
    void marcheazaCaPlatita();
    void aplicaDiscount(float procentDiscount);
    void genereazaDataCurenta();
    std::string genereazaDataCurenta2();

    // Supraincarcare de operatori
    friend std::ostream& operator<<(std::ostream& os, const Factura& factura);
    friend std::istream& operator>>(std::istream& is, Factura& factura);
};

#endif // FACTURA_H
