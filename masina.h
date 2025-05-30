#ifndef MASINA_H
#define MASINA_H

#include <string>
#include <iostream>

template <typename Proprietar>
class Masina {
private:
    std::string nrInmatriculare;
    std::string marca;
    std::string model;
    Proprietar proprietar;

public:
    // Constructor implicit
    Masina()
        : nrInmatriculare("-"), marca("-"), model("-"), proprietar(Proprietar()) {}

    // Constructor cu parametri
    Masina(const std::string& nrInmatriculare,
           const std::string& marca,
           const std::string& model,
           const Proprietar& proprietar)
        : nrInmatriculare(nrInmatriculare), marca(marca), model(model), proprietar(proprietar) {}

    // Constructor de copiere
    Masina(const Masina<Proprietar>& other)
        : nrInmatriculare(other.nrInmatriculare),
          marca(other.marca),
          model(other.model),
          proprietar(other.proprietar) {}

    // Operator= de copiere
    Masina<Proprietar>& operator=(const Masina<Proprietar>& other) {
        if (this != &other) {
            nrInmatriculare = other.nrInmatriculare;
            marca = other.marca;
            model = other.model;
            proprietar = other.proprietar;
        }
        return *this;
    }

    // Destructor
    ~Masina() {}

    // Getteri
    std::string getNrInm() const { return nrInmatriculare; }
    std::string getMarca() const { return marca; }
    std::string getModel() const { return model; }
    Proprietar getProprietar() const { return proprietar; }

    // Setteri
    void setNrInm(const std::string& nrInmatriculare) { this->nrInmatriculare = nrInmatriculare; }
    void setMarca(const std::string& marca) { this->marca = marca; }
    void setModel(const std::string& model) { this->model = model; }
    void setProprietar(const Proprietar& proprietar) { this->proprietar = proprietar; }

    // Operator prieten pentru citire
    template <typename P>
    friend std::istream& operator>>(std::istream& is, Masina<P>& masina);

    // Operator prieten pentru afisare
    template <typename P>
    friend std::ostream& operator<<(std::ostream& os, const Masina<P>& masina);

    // Funcție liberă template friend, care afișează doar marca
    template <typename P>
    friend void afiseazaMarca(const Masina<P>& masina);
};

// Definiție operator >> (citire)
template <typename P>
std::istream& operator>>(std::istream& is, Masina<P>& masina) {
    std::string nrInmatriculare, marca, model;
    P proprietar;

    is >> nrInmatriculare >> marca >> model >> proprietar;
    masina.setNrInm(nrInmatriculare);
    masina.setMarca(marca);
    masina.setModel(model);
    masina.setProprietar(proprietar);

    return is;
}

// Definiție operator << (afișare)
template <typename P>
std::ostream& operator<<(std::ostream& os, const Masina<P>& masina) {
    os << "Datele masinii clientului "
       << masina.proprietar.getNume() << ":\n"
       << "- Numar de inmatriculare: " << masina.nrInmatriculare << '\n'
       << "- Marca: " << masina.marca << '\n'
       << "- Model: " << masina.model << '\n';
    return os;
}

// Implementare funcție liberă template friend, care afișează doar marca
template <typename P>
void afiseazaMarca(const Masina<P>& masina) {
    std::cout << "Marca masinii este: " << masina.marca << std::endl;
}


#endif // MASINA_H
