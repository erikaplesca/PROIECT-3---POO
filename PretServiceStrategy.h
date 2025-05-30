#ifndef PRET_SERVICE_STRATEGY_H
#define PRET_SERVICE_STRATEGY_H

class PretServiceStrategy {
public:
    virtual double calculeazaPret(double baza) const = 0;
    virtual ~PretServiceStrategy() = default;
};

#endif
