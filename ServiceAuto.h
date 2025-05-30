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
