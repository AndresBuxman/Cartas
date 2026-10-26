#ifndef FABRICAELEMENTOS_H
#define FABRICAELEMENTOS_H

#include "elemento.h"

// Crea elementos por id o al azar. Usa un registro (mapa id -> constructor),
// asi agregar un elemento nuevo es registrarlo, sin tocar if/switch.
class FabricaElementos
{
public:
    // Lanza std::invalid_argument si el id no esta registrado.
    static Elemento* crear(int id);
    static Elemento* crearAleatorio(bool incluirMixtos);
};

#endif // FABRICAELEMENTOS_H
