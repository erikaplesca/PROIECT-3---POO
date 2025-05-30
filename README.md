# Proiect3-POO

<h5>Autor: Plesca Maria-Erika, grupa 133</h5>

## <h2>Introducere</h2>
Acest proiect reprezintă un sistem complet de gestionare a unui service auto, care include:
- Gestionarea clienților și mașinilor
- Crearea și administrarea facturilor
- Managementul reparațiilor și serviciilor
- Rapoarte financiare și de stare

## <h2> ✅Implementarea clasei template: `Masina`</h2>


Clasa originală `Masina` era rigidă, putând stoca doar proprietari de tip `Client`. Prin transformarea ei într-un șablon, am obținut o **flexibilitate sporită** și o **reutilizare a codului**:

**⬅️ Înainte** 
```cpp
class Masina {
    // ...
    Client m_proprietar; // Tip fix
};
```

**🔁 După implementarea șablon:**
```cpp
template <typename Proprietar>
class Masina {
    // ...
    Proprietar proprietar; // Tip generic
};
```

### <h3>Beneficii:</h3>
-  **Abstracție crescută**: Putem folosi orice tip ca proprietar
-  **Extensibilitate**: Adăugarea de noi tipuri de proprietari fără modificări

Exemple de utilizare:
```cpp
Masina<Client> masinaStandard; // Foloseste structura existenta
Masina<Angajat> masinaCompanie; // În cazul în care mașina aparține unui angajat.
```

## <h2> ✅ Atribut dependent de tipul Template</h2>
Am adăugat un atribut generic `Proprietar` care depinde de parametrul template:

```cpp
template <typename Proprietar>
class Masina {
    // ...
    Proprietar proprietar; //  Atribut dependent de T
};
```

Acest atribut permite:
- Stocarea oricărui tip de proprietar
- Accesarea datelor proprietarului prin metode specifice

## <h2>✅ Funcție membră dependentă de tipul șablon</h2>
Am implementat metode care depind direct de tipul template:

```cpp
Proprietar getProprietar() const { 
    return proprietar;
}

void setProprietar(const Proprietar& proprietar) { 
    this->proprietar = proprietar;
}
```

Aceste metode:
- Asigură acces la atribut
- Permit manipularea proprietarului independent de tip

## <h2>✅ Implementare de funcții libere șablon (Friend)</h2>
Am adăugat funcții template prietene pentru Citire/Afișare și o operație specifica:

### <h3>Operator de citire/Afișare</h3>
```cpp
template <typename P>
friend std::istream& operator>>(std::istream& is, Masina<P>& masina);

template <typename P>
friend std::ostream& operator<<(std::ostream& os, const Masina<P>& masina);
```

### <h3>Funcție specializată pentru afișare</h3>
Aceasta functie afiseaza doar marca masinii si este `friend`.
```cpp
template <typename P>
friend void afiseazaMarca(const Masina<P>& masina) {
    std::cout << "Marca masinii este: " << masina.marca << std::endl;
}
```

## <h2>✅ 3 Design Patterns implementate</h2>

### <h3>1. Factory Pattern (Pattern de creare)</h3>
<h4>Ce este?</h4>
Factory Pattern centralizează și simplifică logica de creare a obiectelor complexe, permițând instanțierea entităților (ex: Client, Masina) fără a apela direct constructorii lor.

<h4>Implementare</h4>

In `ClientFactory` și `MasinaClientFactory`
- Am creat o clasă ClientFactory, cu o metodă statică create, care construiește și returnează obiecte de tip Client.
- Am creat o clasă MasinaClientFactory, cu o metodă statică create, care construiește și returnează obiecte de tip Masina<Client>.
- În meniul aplicației, atunci când se adaugă o mașină, folosesc aceste Factory-uri pentru a crea atât clientul, cât și mașina, nu constructorii direct.

```cpp
class ClientFactory {
public:
    static Client create(const std::string& nume, const std::string& tip) {
        return Client(nume, tip);
    }
};

class MasinaClientFactory {
public:
    static Masina<Client> create(const std::string& nrInm, 
                                const std::string& marca,
                                const std::string& model,
                                const Client& proprietar) {
        return Masina<Client>(nrInm, marca, model, proprietar);
    }
};
```
<br>

**⬅️ Înainte așa citeam datele de tip Client** 
```cpp
if (OPTIUNE == 1)
			{
				// Citirea unui nou client
				Client client;
				fin >> client;
				listaClienti.push_back(client);
			}
```

**🔁 După implementare `ClientFactory`**
```cpp
std::string nume, tipClient;
				Client client = ClientFactory::create(nume, tipClient);
				listaClienti.push_back(client);
```
<br>
<br>

**⬅️ Înainte așa citeam datele de tip Masina**
```cpp
Masina masina;
				fin >> masina;
				listaMasini.push_back(masina);
```
**🔁După implementare `ClientFactory`**
```cpp
std::string nume, tipClient, nr, marca, model;
				std::cin >> nume >> tipClient;
				Client client = ClientFactory::create(nume, tipClient);

				std::cin >> nr >> marca >> model;
				Masina<Client> masina = MasinaClientFactory::create(nr, marca, model, client);

				listaMasini.push_back(masina);
```

**Beneficii:**
- Încapsulează logica de creare a obiectelor
- Simplifică adăugarea de noi tipuri de obiecte

### <h3>2. Strategy Pattern (Behavioral)</h3>
<h4>Ce este?</h4>
Strategy Pattern permite schimbarea dinamică a unei logici (ex: calculul prețului pentru un serviciu, filtrarea sau sortarea) fără a modifica clasele de bază.

<h4>Implementare</h4>
- Am definit o interfață PretServiceStrategy cu metoda virtuală calculeazaPret.
- Am implementat mai multe strategii concrete (ex: PretStandard, PretPremium, PretDiscount).
- Clasa ServiceAuto poate primi oricând o strategie diferită pentru calculul prețului, fără să fie nevoie să-i modific codul intern.

- Vrem să putem calcula prețul unui serviciu în mai multe moduri:
Standard (fără adaos)
Premium (cu adaos de 50%)
Discount (cu reducere)

Avem clasa de baza PretServiceStrategy:
```cpp

class PretServiceStrategy {
public:
    virtual double calculeazaPret(double baza) const = 0;
    virtual ~PretServiceStrategy() = default;
};
```

Din aceasta, facem const override cu functiile specifice calcularii fiecarui tip de pret:
```cpp
class PretStandard : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza;
    }
};


class PretPremium : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza * 1.5;
    }
};

class PretDiscount : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza * 0.8;
    }
};

```

Apoi, setam strategia potrivita în contextul ServiceAuto:
```cpp
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

**Beneficii:**
- Permite schimbarea dinamică a strategiilor de preț
- Încapsulează algoritmii de calcul
- Ușurează adăugarea de noi politici de preț

Am implementat in main.cpp prin crearea unei noi optiuni, OPTIUNEA 13, care citeste un nr. factura si un tip de pret care sa fie calculat, si foloseste strategia potrivita de calculare a pretului.

```cpp
		if (OPTIUNE == 13) {
				int nrFactura;
				std::string tipPret;
				fin >> nrFactura >> tipPret;
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
				} else {std::cout << "Tip de pret necunoscut!\n";
					continue;
				}
				service.setStrategie(strategie);
				double pretBaza = it->calculeazaTotalCuTVA();
				double pretFinal = service.calculeazaPretFinal(pretBaza);
				std::cout << "Pretul final pentru factura " << nrFactura << " este: " << pretFinal << " RON\n";
				delete strategie;
			}
```

### <h3>3. Singleton Pattern (Logger)</h3>
**Implementare:** `Logger` pentru înregistrarea activităților

```cpp
class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        logfile << message << std::endl;
    }
    
    // Eliminăm copierea
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() : logfile("log.txt", std::ios_base::app) {}
    ~Logger() { if (logfile.is_open()) logfile.close(); }

    std::ofstream logfile;
    std::mutex mtx;
};
```

## <h2>Bibliografie</h2>
https://refactoring.guru/design-patterns/strategy/cpp/example <br>
https://stackoverflow.com/questions/11459294/is-there-a-way-of-implementing-the-strategy-pattern-using-variadic-templates <br>


