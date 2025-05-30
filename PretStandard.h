#include "PretServiceStrategy.h"
class PretStandard : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza;
    }
};
