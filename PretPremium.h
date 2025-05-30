#include "PretServiceStrategy.h"
class PretPremium : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza * 1.5;
    }
};
