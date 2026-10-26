#ifndef TIERRA_H
#define TIERRA_H

#include "elemento.h"

class Tierra : public Elemento
{
public:
    explicit Tierra(float energiaInicial = 100.0f);
};

#endif // TIERRA_H
