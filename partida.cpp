#include "partida.h"

#include <cstring>

namespace {

int exportarElementos(const Jugador& jugador, ElementoGuardado* destino)
{
    int cantidad = 0;
    for (const Elemento* e : jugador.getElementos()) {
        if (cantidad >= MAX_ELEMENTOS) break;
        destino[cantidad++] = e->exportar();
    }
    return cantidad;
}

} // namespace

Partida::Partida(Jugador* jugador, IAJugador* iaJugador, const TablaDanio& tabla)
    : jugador(jugador), iaJugador(iaJugador), tablaDanio(tabla), turno(0) {}

Partida::~Partida()
{
    delete jugador;
    delete iaJugador;
}

bool Partida::setElementoActivoJugador(const Elemento* elemento)
{
    return jugador->setElementoActivo(elemento);
}

ResultadoAtaque Partida::atacar(Jugador& atacante, Jugador& defensor)
{
    Elemento* delAtacante = atacante.getElementoActivo();
    Elemento* delDefensor = defensor.getElementoActivo();

    const float antes = delDefensor->getEnergia();
    delAtacante->atacar(*delDefensor, tablaDanio);
    const float danioReal = antes - delDefensor->getEnergia();

    return ResultadoAtaque(atacante.getNombre(), delAtacante->getNombre(),
                           defensor.getNombre(), delDefensor->getNombre(),
                           danioReal, !delDefensor->estaVivo());
}

std::vector<ResultadoAtaque> Partida::ejecutarRonda()
{
    std::vector<ResultadoAtaque> resultados;

    Elemento* elegidoHumano = jugador->getElementoActivo();
    if (hayGanador() || elegidoHumano == nullptr || !elegidoHumano->estaVivo())
        return resultados;

    Elemento* elegidoIA = iaJugador->seleccionarElementoIA(elegidoHumano, tablaDanio);
    iaJugador->setElementoActivo(elegidoIA);

    resultados.push_back(atacar(*jugador, *iaJugador));

    // Un elemento eliminado no contraataca.
    if (iaJugador->getElementoActivo()->estaVivo())
        resultados.push_back(atacar(*iaJugador, *jugador));

    ++turno;
    return resultados;
}

bool Partida::hayGanador() const
{
    return !jugador->tieneElementosVivos() || !iaJugador->tieneElementosVivos();
}

Jugador* Partida::getGanador() const
{
    if (!jugador->tieneElementosVivos()) return iaJugador;
    if (!iaJugador->tieneElementosVivos()) return jugador;
    return nullptr;
}

Jugador* Partida::getJugador() const { return jugador; }
IAJugador* Partida::getIA() const { return iaJugador; }
const TablaDanio& Partida::getTablaDanio() const { return tablaDanio; }
int Partida::getTurno() const { return turno; }
void Partida::setTurno(int nuevoTurno) { turno = nuevoTurno < 0 ? 0 : nuevoTurno; }

PartidaGuardada Partida::exportar() const
{
    PartidaGuardada estado{};
    estado.magic = MAGIC_PARTIDA;
    estado.version = VERSION_PARTIDA;
    std::strncpy(estado.nombreJugador, jugador->getNombre().c_str(), MAX_NOMBRE - 1);
    estado.idIA = iaJugador->getIdIA();
    estado.turno = turno;

    estado.cantidadJugador = exportarElementos(*jugador, estado.jugador);
    estado.activoJugador = jugador->getIndiceElementoActivo();
    estado.cantidadIA = exportarElementos(*iaJugador, estado.ia);
    estado.activoIA = iaJugador->getIndiceElementoActivo();
    return estado;
}
