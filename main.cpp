// DESCRIEREA PROBLEMEI
//  |-  Acest program C++ gestionează operațiunile unui service auto,
//		oferind următoarele funcționalități:
	// -- Administrarea clienților și a mașinilor acestora
	// -- Gestiunea angajaților service-ului
	// -- Înregistrarea și urmărirea reparațiilor efectuate
	// -- Generarea de rapoarte și liste pentru toate entitățile gestionate



// STRUCTURA PROGRAMULUI
//	|-	Programul este modularizat în patru clase principale:

	// Client - gestionează informații despre clienții service-ului
	// Masina - stochează date despre vehiculele clienților
	// Angajat - menține informații despre angajații service-ului
	// Reparatie - înregistrează detalii despre intervențiile efectuate



// DESCRIEREA DATELOR DE INTRARE
//  |-  Programul citește datele dintr-un fișier text numit "input.in".

//		Acesta conține, pe rând, un numar care indică opțiunea
//		pe care utlizatorul o alege, urmat de datele acelei operatii.



//	DESCRIEREA OPERATIILOR POSIBILE
//	--- Optiunea 1
//		- Citire de clienti
//		- Format citire: [Numele clientului] [Tip client]

//	--- Optiunea 2
//		- Afisarea tuturor clientilor
//		[Nu mai trebuie citit nimic]

//  --- Optiunea 3
//		- Citirea unei noi masini
//		- Format citire:
//		[Nr.Inm] [Marca] [Model] [Nume proprietar] [Tip proprietar]

//  --- Optiunea 4
//		- Afisarea tuturor masinilor
//		[Nu mai trebuie citit nimic]

//  --- Optiunea 5
//		- Citirea unui nou angajat
//		- Format citire: [Numele angajatului] [Statia de lucru]

//  --- Optiunea 6
//		- Afisarea tuturor angajatilor
//		[Nu mai trebuie citit nimic]

//  --- Optiunea 7
//		- Citirea unei noi reparatii
//		- Format citire:
//		[Nr.Inm] [Marca] [Model] [Nume proprietar] [Tip proprietar]
//		[Nume angajat] [Statia de lucru] [Tip reparatie] [Cost]

//  --- Optiunea 8
//		- Afisarea tuturor reparatiilor
//		[Nu mai trebuie citit nimic]

// --- Optiunea 9
//		- Interschimbarea statiilor de lucru intre doua reparatii
//		[Nr. Reparatiei 1] [Nr. Reparatiei 2]

// --- Optiunea 10
//		- Afisarea sumei totale de plata pentru un anumit client
//		[Numele clientului]


// FLUXUL DE DATE

// Datele sunt citite din fișierul de intrare,
// procesate în funcție de opțiunea selectată,
// iar rezultatele sunt afișate pe ecran.

// Programul oferă o interfață simplă de gestionare
// a tuturor entităților unui service auto.
#include "angajat.h"
#include "client.h"
#include "masina.h"
#include "reparatie.h"
#include "factura.h"

#include "masina_factory.h"
#include "client_factory.h"

#include "PretServiceStrategy.h"
#include "PretStandard.h"
#include "PretDiscount.h"
#include "PretPremium.h"
#include "ServiceAuto.h"

#include "logger.h"

#include "ServiceException.h"
#include "serviciu.h"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

std::ifstream fin("input2.in");


	// DECLARAREA VECTORILOR:
std::vector<Masina<Client>> listaMasini;
// --------------------
std::vector<Reparatie> listaReparatii;
// --------------------
std::vector<Client> listaClienti;
// --------------------
std::vector<Angajat> listaAngajati;
// --------------------
std::vector<Factura> listaFacturi;



static int OPTIUNE;

int main()
{
	try
	{if (!fin)
	{
		std::cerr << "Eroare la deschiderea fisierului!\n";
		return 1;
	}
	else
	{
		while (fin >> OPTIUNE)
		{
				if (OPTIUNE == 1)
			{
				// Citirea unui nou client
				std::string nume, tipClient;
				Client client = ClientFactory::create(nume, tipClient);
				listaClienti.push_back(client);
				Logger::getInstance().log("Client adaugat: " + client.getNume() + ", tip: " + client.getTipClient());
			}
			else if (OPTIUNE == 2)
			{
				// Afisarea tuturor clientilor
				Logger::getInstance().log("Afisare lista clienti.");
				for (const auto& client : listaClienti) {
					std::cout << client << "\n";
				}
			}
			else if (OPTIUNE == 3)
			{
				std::string nume, tipClient, nr, marca, model;
				std::cin >> nume >> tipClient;
				Client client = ClientFactory::create(nume, tipClient);

				std::cin >> nr >> marca >> model;
				Masina<Client> masina = MasinaClientFactory::create(nr, marca, model, client);

				listaMasini.push_back(masina);
				Logger::getInstance().log("Masina adaugata: " + nr + ", marca: " + marca + ", model: " + model + ", proprietar: " + nume);
			}
			else if (OPTIUNE == 4)
			{
				Logger::getInstance().log("Afisare lista masini.");
				for (const auto& masina : listaMasini) {
					std::cout << masina << "\n";
				}
			}
			else if (OPTIUNE == 5)
			{
				Angajat angajat;
				fin >> angajat;
				listaAngajati.push_back(angajat);
				Logger::getInstance().log("Angajat adaugat: " + angajat.getNume());
			}
			else if (OPTIUNE == 6)
			{
				Logger::getInstance().log("Afisare lista angajati.");
				for (const auto& angajat : listaAngajati) {
					std::cout << angajat << "\n";
				}
			}
			else if (OPTIUNE == 7)
			{
				try {
					Reparatie reparatie;
					fin >> reparatie;
					const auto& masinaReparatie = reparatie.getMasina();
					auto it = std::find_if(listaMasini.begin(), listaMasini.end(),
						[&](const Masina<Client>& m) { return m.getNrInm() == masinaReparatie.getNrInm(); });

					if (it == listaMasini.end()) {
						listaMasini.push_back(masinaReparatie);
						std::cout << "!!! Masina " << masinaReparatie.getNrInm() << " a fost adaugata in istoric\n";
						Logger::getInstance().log("Masina adaugata in istoric la reparatie: " + masinaReparatie.getNrInm());
					}
					listaReparatii.push_back(reparatie);
					Logger::getInstance().log("Reparatie adaugata pentru masina: " + masinaReparatie.getNrInm());
				}
				catch (const TipServiciuInvalidException& e) {
					Logger::getInstance().log(std::string("Serviciu invalid ignorat: ") + e.what());
					std::cout << "Serviciu invalid ignorat: " << e.what() << "\n";
					continue;
				}
				catch (const TipProprietarInvalidException& e) {
					Logger::getInstance().log(std::string("Eroare proprietar invalid la adaugare reparatie: ") + e.what());
					std::cout << "Eroare: " << e.what() << '\n';
				}
			}
			else if (OPTIUNE == 8)
			{
				Logger::getInstance().log("Afisare lista reparatii.");
				for (const auto& reparatie : listaReparatii) {
					std::cout << reparatie << "\n";
				}
			}
			else if (OPTIUNE == 9)
			{
				size_t i, j;
				fin >> i >> j;
				if (i < listaReparatii.size() && j < listaReparatii.size()) {
					Reparatie::interschimbareStatieLucru(listaReparatii[i], listaReparatii[j]);
					Logger::getInstance().log("Inter schimbare statii lucru intre reparatiile " + std::to_string(i) + " si " + std::to_string(j));
				} else {
					Logger::getInstance().log("Incercare esuata de interschimbare statii lucru: indici invalidi.");
					std::cout << "Indici invalizi pentru reparatii!\n";
				}
			}
			else if (OPTIUNE == 10)
			{
				try {
					Factura factura;
					fin >> factura;
					if (factura.getDataEmitere() == "01/01/2025") {
						factura.genereazaDataCurenta();
					}
					factura.actualizeazaTotal();
					std::string DATA_CURENTA;
					DATA_CURENTA = factura.genereazaDataCurenta2();
					if (factura.getDataEmitere() > DATA_CURENTA)
						throw DataInvalidaException(factura.getDataEmitere());
					for (const auto& f : listaFacturi)
						if (f.getNrFactura() == factura.getNrFactura())
							throw NumarFacturaDuplicatException(factura.getNrFactura());
					std::cout << "\n------------ Generare Factura Noua ------------\n";
					std::cout << factura;
					listaFacturi.push_back(factura);
					Logger::getInstance().log("Factura noua generata: #" + std::to_string(factura.getNrFactura()) + ", client: " + factura.getClient().getNume());
				}
				catch (const DataInvalidaException& e) {
					Logger::getInstance().log(std::string("Eroare data factura: ") + e.what());
					std::cout << "Data" << e.what() << " este invalida." << "\n";
					continue;
				}
				catch (const NumarFacturaDuplicatException& e) {
					Logger::getInstance().log(std::string("Eroare factura duplicata: ") + e.what());
					std::cout << "Nr de factura duplicat: " << e.what() << "\n";
					continue;
				}
			}
			else if (OPTIUNE == 11)
			{
				int idFactura;
				size_t i = 0;
				fin >> idFactura;
				bool gasita = false;
				while (i < listaFacturi.size())
				{
					if (idFactura == listaFacturi[i].getNrFactura())
					{
						std::cout << "\n------------ Detalii Factură ------------\n \n";
						std::cout << listaFacturi[i];
						Logger::getInstance().log("Afisare detalii factura: #" + std::to_string(idFactura));
						gasita = true;
					}
					i++;
				}
				if (!gasita) {
					Logger::getInstance().log("Factura inexistenta la afisare: #" + std::to_string(idFactura));
					std::cout << "Factura inexistenta!\n";
				}
			}
			else if (OPTIUNE == 12)
			{
				std::string NUME_CLIENT;
				float SUMA = 0.0f;
				fin >> NUME_CLIENT;
				bool clientGasit = false;
				for (const auto& factura : listaFacturi)
					if (factura.getClient().getNume() == NUME_CLIENT) {
						clientGasit = true;
						break;
					}
				if (!clientGasit) {
					Logger::getInstance().log("Incercare raport neplati pentru client inexistent: " + NUME_CLIENT);
					std::cout << "Clientul " << NUME_CLIENT << " nu există în sistem!\n";
				}
				else {
					std::vector<Factura*> facturiNeplatite;
					for (auto it = listaFacturi.begin(); it != listaFacturi.end(); ++it)
						if (it->getClient().getNume() == NUME_CLIENT && !it->getPlatita())
						{
							SUMA += it->calculeazaTotalCuTVA();
							facturiNeplatite.push_back(&(*it));
						}
					Logger::getInstance().log("Raport neplati generat pentru client: " + NUME_CLIENT + ", facturi neplatite: " + std::to_string(facturiNeplatite.size()));
					std::cout << "\n----- Raport neplăți client " << NUME_CLIENT << " -----\n";
					if (facturiNeplatite.empty()) {
						std::cout << "Clientul nu are facturi neplătite.\n";
					}
					else {
						for (const auto& factura : facturiNeplatite) {
							std::cout << "Factura #" << factura->getNrFactura()
									<< " - Total: " << factura->calculeazaTotalCuTVA()
									<< " RON (Data: " << factura->getDataEmitere() << ")\n";
						}
						std::cout << "\nTotal de plată: " << SUMA << " RON\n";
					}
				}
			}
			else if (OPTIUNE == 13) {
				int nrFactura;
				std::string tipPret;
				fin >> nrFactura >> tipPret;
				auto it = std::find_if(listaFacturi.begin(), listaFacturi.end(),
					[nrFactura](const Factura& f) { return f.getNrFactura() == nrFactura; });
				if (it == listaFacturi.end()) {
					Logger::getInstance().log("Incercare calcul pret pentru factura inexistenta: #" + std::to_string(nrFactura));
					std::cout << "Factura nu a fost gasita!\n";
					continue;
				}
				ServiceAuto service;
				PretServiceStrategy* strategie = nullptr;
				if (tipPret == "standard") {
					strategie = new PretStandard();
				} else if (tipPret == "premium") {
					strategie = new PretPremium();
				} else if (tipPret == "discount") {
					strategie = new PretDiscount();
				} else {
					Logger::getInstance().log("Tip de pret necunoscut la calcul pret factura: " + tipPret);
					std::cout << "Tip de pret necunoscut!\n";
					continue;
				}
				service.setStrategie(strategie);
				double pretBaza = it->calculeazaTotalCuTVA();
				double pretFinal = service.calculeazaPretFinal(pretBaza);
				Logger::getInstance().log("Pret calculat pentru factura #" + std::to_string(nrFactura) + ", tip pret: " + tipPret + ", valoare: " + std::to_string(pretFinal));
				std::cout << "Pretul final pentru factura " << nrFactura << " este: " << pretFinal << " RON\n";
				delete strategie;
			}
		}
	}
}
    catch (const ServiceException& e) {
        std::cout << "Eroare de service: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Eroare neprevazuta: " << e.what() << "\n";
    }
	return 0;
}