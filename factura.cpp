#include "factura.h"
#include "ServiceException.h"

#include <iomanip>
#include <ctime>
#include <string>
// ------- CONSTRUCTOR IMPLICIT PENTRU CLASA "Factura" -------
Factura::Factura() {
    m_clientCurent = Client();
    m_dataEmitere = "01/01/2025";
    m_nrFactura = 0;
    m_total = 0.0f;
    m_tva = 19.0f;
    m_platita = false;
}

// ------- CONSTRUCTOR DE INITIALIZARE CU PARAMETRI PENTRU CLASA "Factura" -------
Factura::Factura(const Client& clientCurent, 
                 const std::vector<Reparatie>& reparatii,
                 const std::string& dataEmitere,
                 const int& nrFactura,
                 const float& tva,
                 const bool& platita) {
    this->m_clientCurent = clientCurent;
    this->m_reparatii = reparatii;
    this->m_dataEmitere = dataEmitere;
    this->m_nrFactura = nrFactura;
    this->m_tva = tva;
    this->m_platita = platita;
    
    // Calculăm totalul bazat pe toate reparațiile
    actualizeazaTotal();
}

// ------- DESTRUCTORUL PENTRU CLASA "Factura" -------
Factura::~Factura() {}

// ------- CONSTRUCTOR DE COPIERE PENTRU CLASA "Factura" -------
Factura::Factura(const Factura& factura) {
    this->m_clientCurent = factura.m_clientCurent;
    this->m_reparatii = factura.m_reparatii;
    this->m_dataEmitere = factura.m_dataEmitere;
    this->m_nrFactura = factura.m_nrFactura;
    this->m_total = factura.m_total;
    this->m_tva = factura.m_tva;
    this->m_platita = factura.m_platita;
}

// ------- CONSTRUCTORUL DE COPIERE PRIN OPERATORUL "=" -------
Factura& Factura::operator=(const Factura& factura) {
    if (this != &factura) {
        this->m_clientCurent = factura.m_clientCurent;
        this->m_reparatii = factura.m_reparatii;
        this->m_dataEmitere = factura.m_dataEmitere;
        this->m_nrFactura = factura.m_nrFactura;
        this->m_total = factura.m_total;
        this->m_tva = factura.m_tva;
        this->m_platita = factura.m_platita;
    }
    return *this;
}

// ------- GETTER-ELE PENTRU CLASA "Factura" -------
Client Factura::getClient() const {
    return m_clientCurent;
}

std::vector<Reparatie> Factura::getReparatii() const {
    return m_reparatii;
}

Reparatie Factura::getReparatie(int index) const {
    if (index >= 0 && index < static_cast<int>(m_reparatii.size())) {
        return m_reparatii[index];
    }
    return Reparatie(); // Returnează o reparație goală dacă indexul este invalid
}

int Factura::getNumarReparatii() const {
    return m_reparatii.size();
}

std::string Factura::getDataEmitere() const {
    return m_dataEmitere;
}

int Factura::getNrFactura() const {
    return m_nrFactura;
}

float Factura::getTotal() const {
    return m_total;
}

float Factura::getTVA() const {
    return m_tva;
}

bool Factura::getPlatita() const {
    return m_platita;
}

// ------- SETTER-ELE PENTRU CLASA "Factura" -------
void Factura::setClient(const Client& clientCurent) {
    this->m_clientCurent = clientCurent;
}

void Factura::setReparatii(const std::vector<Reparatie>& reparatii) {
    this->m_reparatii = reparatii;
    // Actualizăm automat totalul când se setează reparațiile
    actualizeazaTotal();
}

void Factura::setDataEmitere(const std::string& dataEmitere) {
    this->m_dataEmitere = dataEmitere;
}

void Factura::setNrFactura(const int& nrFactura) {
    this->m_nrFactura = nrFactura;
}

void Factura::setTVA(const float& tva) {
    this->m_tva = tva;
}

void Factura::setPlatita(const bool& platita) {
    this->m_platita = platita;
}

// ------- METODE PENTRU GESTIONAREA REPARAȚIILOR -------
void Factura::adaugaReparatie(const Reparatie& reparatie) {
    m_reparatii.push_back(reparatie);
    // Actualizăm totalul la adăugarea unei noi reparații
    actualizeazaTotal();
}

void Factura::stergeReparatie(int index) {
    if (index >= 0 && index < static_cast<int>(m_reparatii.size())) {
        m_reparatii.erase(m_reparatii.begin() + index);
        // Actualizăm totalul după ștergerea unei reparații
        actualizeazaTotal();
    }
}

// Metoda pentru actualizarea totalului din toate reparațiile
void Factura::actualizeazaTotal() {
    m_total = 0.0f;
    for (const auto& reparatie : m_reparatii) {
        auto serviciu = reparatie.getServiciu();
        if (serviciu) {
            m_total += serviciu->calculeazaCost();
        }
    }
}

// ------- ALTE METODE UTILE PENTRU CLASA "Factura" -------
float Factura::calculeazaTotalCuTVA() const {
    return m_total + (m_total * m_tva / 100.0f);
}

void Factura::marcheazaCaPlatita() {
    m_platita = true;
}

void Factura::aplicaDiscount(float procentDiscount) {
    if (procentDiscount > 0 && procentDiscount <= 100) {
        float discount = m_total * (procentDiscount / 100.0f);
        m_total -= discount;
    }
}

void Factura::genereazaDataCurenta() {
    time_t now = time(0);
    tm* localtm = localtime(&now);
    
    char buffer[11];
    strftime(buffer, 11, "%d/%m/%Y", localtm);
    
    m_dataEmitere = buffer;
}
#include <string>

std::string Factura::genereazaDataCurenta2() {
    time_t now = time(nullptr);
    tm localtm;
    localtime_r(&now, &localtm); // Varianta thread-safe
    
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &localtm);
    return std::string(buffer); // Conversie la std::string
}

// ------- SUPRAINCARCARE DE OPERATORI ">>" SI "<<" (CITIRE SI AFISARE) -------
std::istream& operator>>(std::istream& is, Factura& m_factura) {
    // Citim datele clientului
    Client client;
    std::string nume, tipClient;
    is>>nume>>tipClient;
    client.setNume(nume);
    client.setTipClient(tipClient);
    m_factura.setClient(client);
    
    // Citim datele facturii
    std::string dataEmitere;
    int nrFactura;
    float tva;
    int platita;
    int numarReparatii;
    
    is >> dataEmitere >> nrFactura >> tva >> platita >> numarReparatii;
    
    m_factura.setDataEmitere(dataEmitere);
    m_factura.setNrFactura(nrFactura);
    m_factura.setTVA(tva);
    m_factura.setPlatita(platita != 0);
    
    // Citim reparațiile
    std::vector<Reparatie> reparatii;
    for (int i = 0; i < numarReparatii; i++) {
        Reparatie m_reparatie;
        std::string m_nrInm, m_marca, m_model, m_numeProprietar;
        std::string m_tipProprietar, m_numeAngajat, m_tipReparatie;
        int m_statieLucru;
        Client m_proprietar;
        Masina<Client> m_masina;
        Angajat m_angajat;
        is>>m_nrInm>>m_marca>>m_model
        >>m_numeProprietar>>m_tipProprietar
        >>m_numeAngajat>>m_statieLucru
        >>m_tipReparatie;

        m_masina.setNrInm(m_nrInm);
        m_masina.setMarca(m_marca);
        m_masina.setModel(m_model);

        m_proprietar.setNume(m_numeProprietar);
        m_proprietar.setTipClient(m_tipProprietar);
        m_masina.setProprietar(m_proprietar);

        m_angajat.setNume(m_numeAngajat);
        m_angajat.setStatiaLucru(m_statieLucru);

        m_reparatie.setMasina(m_masina);
        m_reparatie.setAngajat(m_angajat);

        // Alegere serviciu in functie de tip si citire date suplimentare
        std::shared_ptr<Serviciu> serviciu;

        if (m_tipReparatie == "Schimb_ulei") {
            int transmisieInt;
            float cantitateUlei;
            // 0 = Manuala, 1 = Automata
            is >> transmisieInt >> cantitateUlei;
            SchimbUlei::TipTransmisie tipTransmisie = transmisieInt == 1
                ? SchimbUlei::TipTransmisie::Automata
                : SchimbUlei::TipTransmisie::Manuala;
            serviciu = std::make_shared<SchimbUlei>(tipTransmisie, cantitateUlei);
        } else if (m_tipReparatie == "Diagnoza") {
            int nrSisteme;
            is >> nrSisteme;
            serviciu = std::make_shared<Diagnoza>(nrSisteme);
        } else if (m_tipReparatie == "Geometrie_roti") {
            int nrAxe;
            is >> nrAxe;
            serviciu = std::make_shared<GeometrieRoti>(nrAxe);
        } else if (m_tipReparatie == "Electrica") {
            float costPiese;
            is >> costPiese;
            serviciu = std::make_shared<Electrica>(costPiese);
        } else if (m_tipReparatie == "Vopsire") {
            float suprafata;
            is >> suprafata;
            serviciu = std::make_shared<Vopsire>(suprafata);
        } else {
            throw TipServiciuInvalidException(m_tipReparatie);
        }

        m_reparatie.setMasina(m_masina);
        m_reparatie.setAngajat(m_angajat);
        m_reparatie.setServiciu(serviciu);

        reparatii.push_back(m_reparatie);
    }
    
    m_factura.setReparatii(reparatii);
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const Factura& factura) {
    os << "\n============== FACTURA NR. " << factura.getNrFactura() << " ==============\n";
    os << "Data emitere: " << factura.getDataEmitere() << "\n\n";
    
    // Informații despre client
    os << "Client:\n";
    os << "Numele clientului: " << factura.getClient().getNume() << "\n";
    os << "Tipul clientului: " << factura.getClient().getTipClient() << "\n\n";
    
    // Informații despre reparații
    os << "Reparații efectuate:\n";
    for (int i = 0; i < factura.getNumarReparatii(); i++) {
        Reparatie reparatie = factura.getReparatie(i);
        os << "--- Reparația " << (i + 1) << " ---\n";
        os << "Mașină: " << reparatie.getMasina().getMarca() << " " 
           << reparatie.getMasina().getModel() << " (" 
           << reparatie.getMasina().getNrInm() << ")\n";
        os << "Tip reparație: " << reparatie.getTipReparatie() << "\n";
        os << "Angajat responsabil: " << reparatie.getAngajat().getNume() << "\n";
        os << "Stația de lucru: " << reparatie.getAngajat().getStatiaLucru() << "\n";
        os << "Cost: " << std::fixed << std::setprecision(2) << reparatie.getCost() << " RON\n\n";
    }
    
    // Informații despre costuri
    os << "Total fără TVA: " << std::fixed << std::setprecision(2) << factura.getTotal() << " RON\n";
    os << "TVA (" << factura.getTVA() << "%): " << std::fixed << std::setprecision(2) 
       << (factura.getTotal() * factura.getTVA() / 100.0f) << " RON\n";
    os << "Total cu TVA: " << std::fixed << std::setprecision(2) << factura.calculeazaTotalCuTVA() << " RON\n\n";
    
    // Status plată
    os << "Status: " << (factura.getPlatita() ? "PLĂTITĂ" : "NEPLĂTITĂ") << "\n";
    os << "========================================\n";
    
    return os;
}
