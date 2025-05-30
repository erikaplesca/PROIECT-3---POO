#include "reparatie.h"
#include "serviciu.h"
#include "client.h"
#include "ServiceException.h"
#include <vector>
#include <algorithm>
#include <iomanip>

Reparatie::Reparatie()
    : m_masina(), m_angajat(), m_serviciu(nullptr) {}

Reparatie::Reparatie(const Masina<Client>& masina, const Angajat& angajat, std::shared_ptr<Serviciu> serviciu)
    : m_masina(masina), m_angajat(angajat), m_serviciu(serviciu) {}

Reparatie::Reparatie(const Reparatie& other)
    : m_masina(other.m_masina), m_angajat(other.m_angajat),
      m_serviciu(other.m_serviciu ? other.m_serviciu->clone() : nullptr) {}

Reparatie& Reparatie::operator=(const Reparatie& other) {
    if (this != &other) {
        m_masina = other.m_masina;
        m_angajat = other.m_angajat;
        m_serviciu = other.m_serviciu ? other.m_serviciu->clone() : nullptr;
    }
    return *this;
}

Reparatie::~Reparatie() {}

Masina<Client> Reparatie::getMasina() const { return m_masina; }
Angajat Reparatie::getAngajat() const { return m_angajat; }
std::shared_ptr<Serviciu> Reparatie::getServiciu() const { return m_serviciu; }
std::string Reparatie::getTipReparatie() const {
    return m_serviciu ? m_serviciu->getTipServiciu() : "Necunoscut";
}
float Reparatie::getCost() const {
    return m_serviciu ? m_serviciu->calculeazaCost() : 0.0f;
}

void Reparatie::setMasina(const Masina<Client>& masina) { m_masina = masina; }
void Reparatie::setAngajat(const Angajat& angajat) { m_angajat = angajat; }
void Reparatie::setServiciu(std::shared_ptr<Serviciu> serviciu) { m_serviciu = serviciu; }

void Reparatie::setAngajatStatieLucru(int statieLucru) {
    Angajat temp = m_angajat;
    temp.setStatiaLucru(statieLucru);
    m_angajat = temp;
}

std::istream& operator>>(std::istream& is, Reparatie& reparatie) {
    std::string nrInm, marca, model, numeProprietar, tipProprietar;
    std::string numeAngajat, tipReparatie;
    int statieLucru;

    // Citire date masina si client
    is >> nrInm >> marca >> model >> numeProprietar >> tipProprietar;

    if (tipProprietar != "Persoana_fizica" && tipProprietar != "Persoana_juridica")
        throw TipProprietarInvalidException(tipProprietar);

    Client proprietar;
    proprietar.setNume(numeProprietar);
    proprietar.setTipClient(tipProprietar);

    Masina<Client> masina;
    masina.setNrInm(nrInm);
    masina.setMarca(marca);
    masina.setModel(model);
    masina.setProprietar(proprietar);

    // Citire date angajat
    is >> numeAngajat >> statieLucru;
    Angajat angajat;
    angajat.setNume(numeAngajat);
    angajat.setStatiaLucru(statieLucru);

    // Citire tip reparatie
    is >> tipReparatie;

    // Alegere serviciu in functie de tip si citire date suplimentare
    std::shared_ptr<Serviciu> serviciu;

    if (tipReparatie == "Schimb_ulei") {
        int transmisieInt;
        float cantitateUlei;
        // 0 = Manuala, 1 = Automata
        is >> transmisieInt >> cantitateUlei;
        SchimbUlei::TipTransmisie tipTransmisie = transmisieInt == 1
            ? SchimbUlei::TipTransmisie::Automata
            : SchimbUlei::TipTransmisie::Manuala;
        serviciu = std::make_shared<SchimbUlei>(tipTransmisie, cantitateUlei);
    } else if (tipReparatie == "Diagnoza") {
        int nrSisteme;
        is >> nrSisteme;
        serviciu = std::make_shared<Diagnoza>(nrSisteme);
    } else if (tipReparatie == "Geometrie_roti") {
        int nrAxe;
        is >> nrAxe;
        serviciu = std::make_shared<GeometrieRoti>(nrAxe);
    } else if (tipReparatie == "Electrica") {
        float costPiese;
        is >> costPiese;
        serviciu = std::make_shared<Electrica>(costPiese);
    } else if (tipReparatie == "Vopsire") {
        float suprafata;
        is >> suprafata;
        serviciu = std::make_shared<Vopsire>(suprafata);
    } else {
        throw TipServiciuInvalidException(tipReparatie);
    }

    reparatie.setMasina(masina);
    reparatie.setAngajat(angajat);
    reparatie.setServiciu(serviciu);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Reparatie& reparatie) {
    os << "--- Datele masinii:\n"
       << "- Numar inmatriculare: " << reparatie.getMasina().getNrInm() << '\n'
       << "- Marca: " << reparatie.getMasina().getMarca() << '\n'
       << "- Model: " << reparatie.getMasina().getModel() << '\n'
       << "--- Date despre client:\n"
       << "- Numele clientului: " << reparatie.getMasina().getProprietar().getNume() << '\n'
       << "- Tip client: " << reparatie.getMasina().getProprietar().getTipClient() << '\n'
       << "--- Date despre angajatul responsabil de reparatie:\n"
       << "- Numele angajatului: " << reparatie.getAngajat().getNume() << '\n'
       << "- Statia de lucru: " << reparatie.getAngajat().getStatiaLucru() << '\n'
       << "--- Date despre reparatie:\n"
       << "- Tip reparatie: " << reparatie.getTipReparatie() << '\n'
       << "- Costul reparatiei: " << std::fixed << std::setprecision(2) << reparatie.getCost() << " RON\n";

    // Afișare detalii specifice serviciului (exemplu pentru fiecare tip)
    if (reparatie.getServiciu()) {
        if (auto ulei = std::dynamic_pointer_cast<SchimbUlei>(reparatie.getServiciu())) {
            os << "- Transmisie: " << (ulei->getTipTransmisie() == SchimbUlei::TipTransmisie::Automata ? "Automata" : "Manuala") << '\n';
            os << "- Cantitate ulei: " << ulei->getCantitateUlei() << " L\n";
        } else if (auto diag = std::dynamic_pointer_cast<Diagnoza>(reparatie.getServiciu())) {
            os << "- Sisteme verificate: " << diag->getNumarSistemeVerificate() << '\n';
        } else if (auto geo = std::dynamic_pointer_cast<GeometrieRoti>(reparatie.getServiciu())) {
            os << "- Numar axe: " << geo->getNumarAxe() << '\n';
        } else if (auto electrica = std::dynamic_pointer_cast<Electrica>(reparatie.getServiciu())) {
            os << "- Cost piese: " << electrica->getCostPiese() << " RON\n";
        } else if (auto vopsire = std::dynamic_pointer_cast<Vopsire>(reparatie.getServiciu())) {
            os << "- Suprafata vopsita: " << vopsire->getSuprafata() << " mp\n";
        }
    }
    return os;
}

void Reparatie::interschimbareStatieLucru(Reparatie& r1, Reparatie& r2) {
    int aux = r1.getAngajat().getStatiaLucru();
    r1.setAngajatStatieLucru(r2.getAngajat().getStatiaLucru());
    r2.setAngajatStatieLucru(aux);
    std::cout << "Interschimbare realizata cu succes!\n";
}

