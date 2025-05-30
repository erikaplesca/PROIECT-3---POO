# PROIECT-3-POO

<h5>Autor: Plesca Maria-Erika, grupa 133</h5>

<h2> Minim o funcție șablon și o clasă șablon (template)</h2>
✅ Îndeplinit: Am clasa Masina ca template (template <typename Proprietar>). <br><br>
Clasa Masina este acum scrisă cu un parametru de tip generic (template <typename Proprietar>), ceea ce înseamnă că atunci când o instanțiem, putem specifica tipul exact al proprietarului: <br>
O masina la care se lucrează în service nu e neapărat să aparțină unui Client, ci poate aparține și unui Angajat. Astfel, avem flexibilitate.<br>

<h4> ⬅️ Înainte:</h4>

```
class Masina
{
private:
    std::string m_nrInm;
    std::string m_marca;
    std::string m_model;
    Client m_proprietar;

... 
}
```
<h4> 🔁 După:</h4>

```
template <typename Proprietar>
class Masina {
private:
    std::string nrInmatriculare;
    std::string marca;
    std::string model;
    Proprietar proprietar;
...
}
```
   
<br><br>
<h2> Minim un atribut de tip T</h2>
✅ Îndeplinit: Atributul proprietar depinde direct de parametrul template Proprietar. <br><br>

```
Proprietar proprietar;
```

<br><br>
<h2> Minim o funcție membru care să depindă de T (sau de alt parametru template);</h2>
✅ Îndeplinit: Am mai multe funcții membre care depind de Proprietar. <br><br>

<h4>Getter-ul pentru proprietar:</h4>

```
Proprietar getProprietar() const { return proprietar; }
```

<h4>Setter-ul pentru proprietar:</h4>

```
void setProprietar(const Proprietar& proprietar) { this->proprietar = proprietar; }
```
<h4>Constructorul cu parametri:</h4>

```
Masina(const std::string& nrInmatriculare,
       const std::string& marca,
       const std::string& model,
       const Proprietar& proprietar)
```

<br><br>
<h2> Minim o funcție normală/liberă template.</h2>
✅ Îndeplinit: Am funcții template pentru operatorii de intrare și ieșire:<br><br>


O funcție normală/liberă template (free function template) este o funcție independentă de clasă, care poate fi declarată friend pentru a avea acces la membrii privați ai clasei.<br>

```
template <typename P>
friend std::istream& operator>>(std::istream& is, Masina<P>& masina);

template <typename P>
friend std::ostream& operator<<(std::ostream& os, const Masina<P>& masina);
```
<h4> În plus, am implementat și o funcție liberă template friend, care afișează doar marca</h4>

```
template <typename P>
void afiseazaMarca(const Masina<P>& masina) {
    std::cout << "Marca masinii este: " << masina.marca << std::endl;
}
```
<br><br>
<h2> 3 design patterns (unul este singleton)</h2>
✅ Îndeplinit: Factory Pattern, Strategy Pattern și Singleton <br><br>

<h3>1. Factory Pattern (Pattern de creare)</h3>

Am creat o clasă ClientFactory, cu o metodă statică create, care construiește și returnează obiecte de tip Client.<br>

```
#ifndef CLIENT_FACTORY_H
#define CLIENT_FACTORY_H

#include "client.h"
#include <string>

class ClientFactory {
public:
    static Client create(const std::string& nume, const std::string& tipClient) {
        return Client(nume, tipClient);
    }
};

#endif // CLIENT_FACTORY_H

```
<br>
Am creat o clasă MasinaClientFactory, cu o metodă statică create, care construiește și returnează obiecte de tip Masina<Client>.<br>

```
#ifndef MASINA_FACTORY_H
#define MASINA_FACTORY_H

#include "masina.h"
#include "client.h"
#include <string>

class MasinaClientFactory {
public:
    static Masina<Client> create(const std::string& nr, const std::string& marca, const std::string& model, const Client& proprietar) {
        return Masina<Client>(nr, marca, model, proprietar);
    }
};

#endif // MASINA_FACTORY_H
```
<br>
Acum, în meniul aplicației, (opțiunile 1 și 3) folosesc aceste Factory-uri pentru a crea atât clientul, cât și mașina, nu constructorii direct.

```
if (OPTIUNE == 1)
			{
				// Citirea unui nou client
				std::string nume, tipClient;
				Client client = ClientFactory::create(nume, tipClient);
				listaClienti.push_back(client);
			}
```

```
else if (OPTIUNE == 3)
			{
				std::string nume, tipClient, nr, marca, model;
				std::cin >> nume >> tipClient;
				Client client = ClientFactory::create(nume, tipClient);

				std::cin >> nr >> marca >> model;
				Masina<Client> masina = MasinaClientFactory::create(nr, marca, model, client);

				listaMasini.push_back(masina);
			}
```

<br><br>
<h3>2. Strategy Pattern (Pattern comportamental)</h3>

- Este un design pattern care permite alegerea dinamică a unui algoritm sau a unei logici, la runtime, fără a modifica clasa principală.<br>
- Am identificat o logică ce poate varia: calculul prețului pentru o factură (poate fi standard, premium, sau cu discount).<br>
<br>
-Avem o clasă de bază, PretServiceStrategy:

```
#ifndef PRET_SERVICE_STRATEGY_H
#define PRET_SERVICE_STRATEGY_H

class PretServiceStrategy {
public:
    virtual double calculeazaPret(double baza) const = 0;
    virtual ~PretServiceStrategy() = default;
};
#endif
```

- Am creat clasa ServiceAuto, care păstrează o referință la o strategie și o folosește pentru a calcula prețul final. <br>

```
#include "PretServiceStrategy.h"

class ServiceAuto {
    const PretServiceStrategy* strategiePret = nullptr;
public:
    void setStrategie(const PretServiceStrategy* strategie) {
        strategiePret = strategie;
    }
    double calculeazaPretFinal(double baza) const {
        if (!strategiePret) throw std::runtime_error("Strategia nu este setată!");
        return strategiePret->calculeazaPret(baza);
    }
};
```
<br>
- Am implementat mai multe clase concrete (ex: PretStandard, PretPremium, PretDiscount) care definesc fiecare altă formulă de calcul al prețului.

<H4>PretStandard.H</H4>

```

#include "PretServiceStrategy.h"
class PretStandard : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza;
    }
};
```

<H4>PretPremium.H</H4>

```
#include "PretServiceStrategy.h"
class PretPremium : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza * 1.5;
    }
};
```

<H4>PretDiscount.H</H4>

```
#include "PretServiceStrategy.h"
class PretDiscount : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza * 0.8;
    }
};
```

<br> 
Ca să aibă o utilitate în programul meu, am creat o nouă opțiune (OPTIUNEA 13) care citește numărul facturii și tipul de preț care se calculează pentru aceasta. 
<ul>
  <li>Programul caută factura și apoi creează o strategie de calcul potrivită (PretStandard, PretPremium, PretDiscount).</li>
<li>Clasa principală (ServiceAuto) folosește această strategie pentru a calcula prețul final.</li>
<li>Dacă vreau să adaug pe viitor un nou mod de calcul (ex: promoție specială), nu trebuie să modific codul principal, ci doar să adaug o nouă strategie.</li>
</ul>

```
 if (OPTIUNE == 13) {
				int nrFactura;
				std::string tipPret;
				fin >> nrFactura >> tipPret;
			
				// Caută factura
				auto it = std::find_if(listaFacturi.begin(), listaFacturi.end(),
					[nrFactura](const Factura& f) { return f.getNrFactura() == nrFactura; });
			
				if (it == listaFacturi.end()) {
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
					std::cout << "Tip de pret necunoscut!\n";
					continue;
				}
			
				service.setStrategie(strategie);
			
				double pretBaza = it->calculeazaTotalCuTVA(); 
				double pretFinal = service.calculeazaPretFinal(pretBaza);
			
				std::cout << "Pretul final pentru factura " << nrFactura << " este: " << pretFinal << " RON\n";
			
				delete strategie;
			}
```

<br><br>

<h3>3. Logger (Singleton) </h3>
- Am implementat un Logger ca Singleton, adică orice componentă a aplicației poate loga mesaje centralizat, fără riscul de a exista mai multe instanțe de logger. <br>
-Toate mesajele sunt scrise într-un singur fișier ("log.txt"), asigurând trasabilitate și ușurință la depanare. <br>
- Loggerul poate fi folosit oriunde în proiect cu Logger::getInstance().log("mesaj")<br>
<br>

```
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    // Obține instanța unică a loggerului
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // Pentru a scrie un mesaj în fișierul de log
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        logfile << message << std::endl;
    }

    // Asigurarea ca e singleton
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    std::ofstream logfile; // obiect de tip output file stream din biblioteca standard C++ (<fstream>)
    std::mutex mtx; // asa previn ca mesajele să se amestece sau să corup fișierul de log.
    // Mutex-ul proteja accesul la o resursă partajată între mai multe fire de execuție (threads).

    
    // Constructor privat: deschide fișierul de log
    Logger() : logfile("log.txt", std::ios_base::app) {}

    // Destructor: închide fișierul la final
    ~Logger() {
        if (logfile.is_open())
            logfile.close();
    }
};

#endif // LOGGER_H
```

<br>
În main.cpp, am bucăți de genul ăsta: <br>

```
if (OPTIUNE == 1)
			{
				// Citirea unui nou client
				std::string nume, tipClient;
				Client client = ClientFactory::create(nume, tipClient);
				listaClienti.push_back(client);
				Logger::getInstance().log("Client adaugat: " + client.getNume() + ", tip: " + client.getTipClient());
			}
```
<br>
L-am folosit inclusiv ca să loghez erorile:

```
if (OPTIUNE == 7)
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
```
<br>
După ce a rulat programul, așa arată <i>log.txt:</i>

```
Masina adaugata in istoric la reparatie: B123ABC
Reparatie adaugata pentru masina: B123ABC
Masina adaugata in istoric la reparatie: B234DEF
Reparatie adaugata pentru masina: B234DEF
Masina adaugata in istoric la reparatie: B345GHI
Reparatie adaugata pentru masina: B345GHI
Masina adaugata in istoric la reparatie: B456JKL
Reparatie adaugata pentru masina: B456JKL
Masina adaugata in istoric la reparatie: B567MNO
Reparatie adaugata pentru masina: B567MNO
Afisare lista reparatii.
Factura noua generata: #1001, client: Ion_Popescu
Factura noua generata: #1002, client: Maria_Cretu
Eroare factura duplicata: 
 !!!!! 
 Numarul de factura 1002 a mai fost folosit!
 !!!!! 
 
Factura noua generata: #1003, client: Romsilva_SA
Raport neplati generat pentru client: Maria_Cretu, facturi neplatite: 1
Pret calculat pentru factura #1001, tip pret: premium, valoare: 1356.600037
```

<h3>Pentru a asigura că nu se suprascrie log.txt, în Makefile am adaugat sa șteargă și fișierul log.txt la comanda <i>make clean</i></h3>
