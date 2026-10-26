#ifndef IAESTRATEGICA_H
#define IAESTRATEGICA_H

#include "ia.h"

// Elige el elemento con mayor ventaja (daño infligido - daño recibido) frente al oponente.
class IAEstrategica : public IA {
public:
    Elemento* seleccionarIA(const std::vector<Elemento*>& propios,
                            const Elemento* oponenteActivo,
                            const TablaDanio& tabla) override;
    int getId() const override;

protected:
    float calcularVentaja(const Elemento& candidato, const Elemento& oponente,
                          const TablaDanio& tabla) const;

    Elemento* mejorPorVentaja(const std::vector<Elemento*>& propios, const Elemento& oponente,
                              const TablaDanio& tabla) const;
};

#endif // IAESTRATEGICA_H
