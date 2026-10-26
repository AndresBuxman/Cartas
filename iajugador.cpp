#include "iajugador.h"

IAJugador::IAJugador(const std::string& nombre, IA* modo) : Jugador(nombre), modo(modo) {}

IAJugador::~IAJugador()
{
    delete modo;
}

Elemento* IAJugador::seleccionarElementoIA(const Elemento* oponenteActivo, const TablaDanio& tabla)
{
    if (modo == nullptr) return nullptr;
    return modo->seleccionarIA(getElementosVivos(), oponenteActivo, tabla);
}

Elemento* IAJugador::seleccionarElemento()
{
    std::vector<Elemento*> vivos = getElementosVivos();
    return vivos.empty() ? nullptr : vivos.front();
}

int IAJugador::getIdIA() const
{
    return modo->getId();
}
