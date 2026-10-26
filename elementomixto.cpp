#include "elementomixto.h"

ElementoMixto::ElementoMixto(const std::string& nombre, int id,
                             TipoElemento tipoAtaque, TipoElemento tipoDefensa,
                             float energiaInicial)
    : Elemento(nombre, id, tipoAtaque, energiaInicial), tipoDefensa(tipoDefensa) {}

TipoElemento ElementoMixto::getTipoDefensa() const
{
    return tipoDefensa;
}
