#include "serviciu.h"
#include <algorithm>

// Implementare Serviciu
Serviciu::Serviciu(const std::string& tip, int durata, float cost) :
    m_tipServiciu(tip), m_durata(durata), m_costBaza(cost) {}

std::string Serviciu::getTipServiciu() const { return m_tipServiciu; }
int Serviciu::getDurata() const { return m_durata; }
float Serviciu::getCostBaza() const { return m_costBaza; }

// Implementare SchimbUlei
float SchimbUlei::PRET_MANUAL = 30.0f;
float SchimbUlei::PRET_AUTOMAT = 45.0f;

SchimbUlei::SchimbUlei(TipTransmisie transmisie, float cantitate) :
    Serviciu("Schimb Ulei", 45, 50.0f),
    m_transmisie(transmisie),
    m_cantitateUlei(cantitate) {}

float SchimbUlei::calculeazaCost() const {
    float pretLichid = (m_transmisie == TipTransmisie::Automata) 
                      ? PRET_AUTOMAT 
                      : PRET_MANUAL;
    return m_costBaza + (m_cantitateUlei * pretLichid);
}

void SchimbUlei::aplicaDiscount(float procent) {
    m_costBaza *= (1 - procent/100);
}

std::shared_ptr<Serviciu> SchimbUlei::clone() const {
    return std::make_shared<SchimbUlei>(*this);
}

// Implementare Diagnoza
Diagnoza::Diagnoza(int sisteme) :
    Serviciu("Diagnoza", 60, 80.0f),
    m_numarSistemeVerificate(sisteme) {}

float Diagnoza::calculeazaCost() const {
    return m_costBaza + (m_numarSistemeVerificate * 25.0f);
}

void Diagnoza::aplicaDiscount(float procent) {
    m_costBaza *= (1 - procent/100);
}

std::shared_ptr<Serviciu> Diagnoza::clone() const {
    return std::make_shared<Diagnoza>(*this);
}

// Implementare GeometrieRoti
GeometrieRoti::GeometrieRoti(int axe) :
    Serviciu("Geometrie Roti", 90, 120.0f),
    m_numarAxe(axe) {}

float GeometrieRoti::calculeazaCost() const {
    return m_costBaza * m_numarAxe;
}

void GeometrieRoti::aplicaDiscount(float procent) {
    m_costBaza *= (1 - procent/100);
}

std::shared_ptr<Serviciu> GeometrieRoti::clone() const {
    return std::make_shared<GeometrieRoti>(*this);
}

// Implementare Electrica
Electrica::Electrica(float costPiese) :
    Serviciu("Service Electric", 120, 150.0f),
    m_costPiese(costPiese) {}

float Electrica::calculeazaCost() const {
    return m_costBaza + m_costPiese;
}

void Electrica::aplicaDiscount(float procent) {
    m_costBaza *= (1 - procent/100);
    m_costPiese *= (1 - procent/100);
}

std::shared_ptr<Serviciu> Electrica::clone() const {
    return std::make_shared<Electrica>(*this);
}

// Implementare Vopsire
Vopsire::Vopsire(float suprafata) :
    Serviciu("Vopsire", 240, 200.0f),
    m_suprafata(suprafata) {}

float Vopsire::calculeazaCost() const {
    return m_costBaza + (m_suprafata * 80.0f);
}

void Vopsire::aplicaDiscount(float procent) {
    m_costBaza *= (1 - procent/100);
}

std::shared_ptr<Serviciu> Vopsire::clone() const {
    return std::make_shared<Vopsire>(*this);
}
