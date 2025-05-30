#include "PretServiceStrategy.h"
class PretDiscount : public PretServiceStrategy {
public:
    double calculeazaPret(double baza) const override {
        return baza * 0.8;
    }
};
