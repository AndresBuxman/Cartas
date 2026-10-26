#ifndef PARTIDA_H
#define PARTIDA_H

#include <vector>
#include "jugador.h"
#include "iajugador.h"
#include "tabladanio.h"
#include "resultadoataque.h"
#include "estadoguardado.h"

// Reglas de una partida entre un jugador humano y una IA.
// No conoce la interfaz grafica ni los archivos: solo juega y se exporta a un struct.
class Partida
{
private:
    Jugador* jugador;       // dueña de ambos jugadores
    IAJugador* iaJugador;
    TablaDanio tablaDanio;
    int turno;              // rondas jugadas

    ResultadoAtaque atacar(Jugador& atacante, Jugador& defensor);

public:
    Partida(Jugador* jugador, IAJugador* iaJugador, const TablaDanio& tabla);
    ~Partida();

    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    // El humano elige (solo elementos propios vivos). Devuelve false si no es valido.
    bool setElementoActivoJugador(const Elemento* elemento);

    // Juega una ronda: la IA elige, ataca el humano y contraataca la IA si sigue viva.
    // Devuelve los ataques realizados (vacio si no se pudo jugar).
    std::vector<ResultadoAtaque> ejecutarRonda();

    bool hayGanador() const;
    Jugador* getGanador() const;

    Jugador* getJugador() const;
    IAJugador* getIA() const;
    const TablaDanio& getTablaDanio() const;
    int getTurno() const;
    void setTurno(int nuevoTurno);

    // Persistencia: clase -> struct.
    PartidaGuardada exportar() const;
};

#endif // PARTIDA_H
