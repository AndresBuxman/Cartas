#ifndef ELEMENTOSMIXTOS_H
#define ELEMENTOSMIXTOS_H

#include "elementomixto.h"

// Barro (agua + tierra): ataca como Agua, resiste como Tierra.
class Barro : public ElementoMixto {
public:
    explicit Barro(float energiaInicial = 100.0f);
};

// Lava (tierra + fuego): ataca como Fuego, resiste como Tierra.
class Lava : public ElementoMixto {
public:
    explicit Lava(float energiaInicial = 100.0f);
};

// Vapor (agua + fuego): ataca como Fuego, resiste como Agua.
class Vapor : public ElementoMixto {
public:
    explicit Vapor(float energiaInicial = 100.0f);
};

#endif // ELEMENTOSMIXTOS_H
