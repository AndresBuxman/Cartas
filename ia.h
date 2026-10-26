#ifndef IA_H
#define IA_H

#include <vector>
#include "elemento.h"
#include "tabladanio.h"

// Clase abstracta: cada estrategia decide que elemento propio mandar a combatir.
class IA {
public:
    virtual ~IA() = default;

    // Recibe los elementos vivos propios y el elemento activo del oponente.
    virtual Elemento* seleccionarIA(const std::vector<Elemento*>& propios,
                                    const Elemento* oponenteActivo,
                                    const TablaDanio& tabla) = 0;

    // Identificador de la estrategia (se guarda en disco).
    virtual int getId() const = 0;
};

#endif // IA_H
