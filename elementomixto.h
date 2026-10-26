#ifndef ELEMENTOMIXTO_H
#define ELEMENTOMIXTO_H

#include "elemento.h"

// Elemento que ataca con las reglas de un tipo y se defiende con las de otro.
// Ej.: Barro = ataca como Agua, resiste como Tierra.
class ElementoMixto : public Elemento {
private:
    TipoElemento tipoDefensa;

protected:
    ElementoMixto(const std::string& nombre, int id,
                  TipoElemento tipoAtaque, TipoElemento tipoDefensa,
                  float energiaInicial = 100.0f);

public:
    TipoElemento getTipoDefensa() const override;
};

#endif // ELEMENTOMIXTO_H
