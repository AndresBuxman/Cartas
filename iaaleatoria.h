#ifndef IAALEATORIA_H
#define IAALEATORIA_H

#include "ia.h"

// Elige un elemento al azar. No tiene en cuenta ventajas ni desventajas.
class IAAleatoria : public IA {
public:
    Elemento* seleccionarIA(const std::vector<Elemento*>& propios,
                            const Elemento* oponenteActivo,
                            const TablaDanio& tabla) override;
    int getId() const override;
};

#endif // IAALEATORIA_H
