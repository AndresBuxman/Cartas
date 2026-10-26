#ifndef IAJUGADOR_H
#define IAJUGADOR_H

#include "jugador.h"
#include "ia.h"

// Jugador controlado por la maquina. Compone una estrategia (IA) y es su dueño.
class IAJugador : public Jugador {
private:
    IA* modo;

public:
    IAJugador(const std::string& nombre, IA* modo);
    ~IAJugador() override;

    IAJugador(const IAJugador&) = delete;
    IAJugador& operator=(const IAJugador&) = delete;

    Elemento* seleccionarElementoIA(const Elemento* oponenteActivo, const TablaDanio& tabla);
    Elemento* seleccionarElemento() override;

    int getIdIA() const;
};

#endif // IAJUGADOR_H
