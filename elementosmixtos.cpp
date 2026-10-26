#include "elementosmixtos.h"
#include "idelemento.h"

Barro::Barro(float energiaInicial)
    : ElementoMixto("Barro", ID_BARRO, TipoElemento::AGUA, TipoElemento::TIERRA, energiaInicial) {}

Lava::Lava(float energiaInicial)
    : ElementoMixto("Lava", ID_LAVA, TipoElemento::FUEGO, TipoElemento::TIERRA, energiaInicial) {}

Vapor::Vapor(float energiaInicial)
    : ElementoMixto("Vapor", ID_VAPOR, TipoElemento::FUEGO, TipoElemento::AGUA, energiaInicial) {}
