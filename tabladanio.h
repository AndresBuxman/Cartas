#ifndef TABLADANIO_H
#define TABLADANIO_H

#include <map>
#include "par.h"
#include "tipoelemento.h"

class Elemento;

// Matriz de efectividad: cuanta energia quita un tipo atacante a un tipo defensor.
// Los valores NO estan fijos en la logica: se cargan desde config.txt
// (porDefecto() solo se usa si el archivo no existe o no define la regla).
class TablaDanio {
private:
    std::map<Par, float> tabla;

public:
    TablaDanio() = default;

    static TablaDanio porDefecto();

    void configurarDanio(TipoElemento atacante, TipoElemento defensor, float porcentajeDanio);

    float getDanio(const Elemento& atacante, const Elemento& defensor) const;
    float getDanio(TipoElemento atacante, TipoElemento defensor) const;

    bool tieneRegla(TipoElemento atacante, TipoElemento defensor) const;

    // Comparacion de ventajas (la usan las IAs).
    bool esMayor(float ventajaA, float ventajaB) const;
};

#endif // TABLADANIO_H
