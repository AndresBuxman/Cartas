#ifndef SUPERIA_H
#define SUPERIA_H

#include "iaestrategica.h"

// Antes de maximizar la ventaja, revisa si puede rematar al oponente en este turno.
// Si varios pueden rematar, usa el de menor energia (cuida a los mas sanos para
// turnos futuros). Si nadie puede rematar, se comporta como IAEstrategica.
class SuperIA : public IAEstrategica {
public:
    Elemento* seleccionarIA(const std::vector<Elemento*>& propios,
                            const Elemento* oponenteActivo,
                            const TablaDanio& tabla) override;
    int getId() const override;
};

#endif // SUPERIA_H
