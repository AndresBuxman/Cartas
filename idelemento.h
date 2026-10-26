#ifndef IDELEMENTO_H
#define IDELEMENTO_H

// Identificador numerico de cada clase concreta de elemento.
// Es lo que se guarda en disco y lo que usa FabricaElementos para reconstruir.
enum IdElemento {
    ID_AGUA   = 0,
    ID_TIERRA = 1,
    ID_FUEGO  = 2,
    ID_BARRO  = 3,
    ID_LAVA   = 4,
    ID_VAPOR  = 5
};

#endif // IDELEMENTO_H
