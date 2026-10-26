#ifndef AGUA_H
#define AGUA_H

#include "elemento.h"

class Agua : public Elemento
{
public:
    explicit Agua(float energiaInicial = 100.0f);
};

#endif // AGUA_H
