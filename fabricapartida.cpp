#include "fabricapartida.h"

#include <memory>
#include "fabricaelementos.h"
#include "fabricaia.h"

namespace {

void restaurarElementos(Jugador& jugador, const ElementoGuardado* origen, int cantidad, int activo)
{
    for (int i = 0; i < cantidad; ++i) {
        Elemento* e = FabricaElementos::crear(origen[i].id);
        e->restaurarEnergia(origen[i].energia);
        jugador.agregarElemento(e);
    }
    jugador.setIndiceElementoActivo(activo);
}

} // namespace

Partida* FabricaPartida::crearNueva(const std::string& nombreJugador, int idIA, const Configuracion& config)
{
    const std::string nombre = nombreJugador.empty() ? "Jugador" : nombreJugador;

    std::unique_ptr<Jugador> humano(new Jugador(nombre));
    std::unique_ptr<IAJugador> cpu(new IAJugador("CPU", FabricaIA::crear(idIA)));

    for (int i = 0; i < config.getCantidadElementos(); ++i) {
        humano->agregarElemento(FabricaElementos::crearAleatorio(config.getElementosMixtos()));
        cpu->agregarElemento(FabricaElementos::crearAleatorio(config.getElementosMixtos()));
    }

    return new Partida(humano.release(), cpu.release(), config.getTablaDanio());
}

Partida* FabricaPartida::crearDesdeEstado(const PartidaGuardada& estado, const Configuracion& config)
{
    std::unique_ptr<Jugador> humano(new Jugador(estado.nombreJugador));
    std::unique_ptr<IAJugador> cpu(new IAJugador("CPU", FabricaIA::crear(estado.idIA)));

    restaurarElementos(*humano, estado.jugador, estado.cantidadJugador, estado.activoJugador);
    restaurarElementos(*cpu, estado.ia, estado.cantidadIA, estado.activoIA);

    std::unique_ptr<Partida> partida(new Partida(humano.release(), cpu.release(), config.getTablaDanio()));
    partida->setTurno(estado.turno);
    return partida.release();
}
