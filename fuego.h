#ifndef FUEGO_H
#define FUEGO_H

#include "elemento.h"

class Fuego : public Elemento
{
public:
    explicit Fuego(float energiaInicial = 100.0f);
};

#endif // FUEGO_H
