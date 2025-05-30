#ifndef SERVICIU_H
#define SERVICIU_H

#include <memory>
#include <string>

// CLASA DE BAZA SERVICIU --------------------------

class Serviciu {
protected:
    std::string m_tipServiciu;
    int m_durata;    // în minute
    float m_costBaza;
    
public:
    Serviciu(const std::string& tip, int durata, float cost);
    Serviciu(const Serviciu& other) = default;
    Serviciu& operator=(const Serviciu& other) = default;
    virtual ~Serviciu() = default;

    virtual float calculeazaCost() const = 0;
    virtual void aplicaDiscount(float procent) = 0;
    virtual std::shared_ptr<Serviciu> clone() const = 0;
    
    std::string getTipServiciu() const;
    int getDurata() const;
    float getCostBaza() const;
};



// CLASELE DERIVATE ------------------------------

        // SCHIMB ULEI --------------------------

class SchimbUlei : public Serviciu {
public:
    enum class TipTransmisie { Automata, Manuala };
    
private:
    TipTransmisie m_transmisie;
    float m_cantitateUlei;
    static float PRET_MANUAL;
    static float PRET_AUTOMAT;

public:
    SchimbUlei(TipTransmisie transmisie, float cantitate);
    float calculeazaCost() const override;
    void aplicaDiscount(float procent) override;
    std::shared_ptr<Serviciu> clone() const override;

    // Definesc inline getterii in header
    TipTransmisie getTipTransmisie() const { return m_transmisie; }
    float getCantitateUlei() const { return m_cantitateUlei; }
};


        //DIAGNOZA --------------------------

class Diagnoza : public Serviciu {
    int m_numarSistemeVerificate;
    
public:
    Diagnoza(int sisteme);
    float calculeazaCost() const override;
    void aplicaDiscount(float procent) override;
    std::shared_ptr<Serviciu> clone() const override;

    int getNumarSistemeVerificate() const { return m_numarSistemeVerificate; }

};


        //GEOMETRIE ROTI --------------------------

class GeometrieRoti : public Serviciu {
    int m_numarAxe;
    
public:
    GeometrieRoti(int axe);
    float calculeazaCost() const override;
    void aplicaDiscount(float procent) override;
    std::shared_ptr<Serviciu> clone() const override;

    int getNumarAxe() const { return m_numarAxe; }

};


        //ELECTRICA --------------------------

class Electrica : public Serviciu {
    float m_costPiese;
    
public:
    Electrica(float costPiese);
    float calculeazaCost() const override;
    void aplicaDiscount(float procent) override;
    std::shared_ptr<Serviciu> clone() const override;

    float getCostPiese() const { return m_costPiese; }

};


        //VOPSIRE --------------------------

class Vopsire : public Serviciu {
    float m_suprafata;
    
public:
    Vopsire(float suprafata);
    float calculeazaCost() const override;
    void aplicaDiscount(float procent) override;
    std::shared_ptr<Serviciu> clone() const override;

    float getSuprafata() const { return m_suprafata; }

};

#endif // SERVICIU_H
