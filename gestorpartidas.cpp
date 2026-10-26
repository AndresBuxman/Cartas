#include "gestorpartidas.h"
#include "fabricapartida.h"

#include <exception>

GestorPartidas::GestorPartidas(const Configuracion& config, const std::string& directorioPartidas,
                               const std::vector<std::string>& advertenciasConfig)
    : config(config), repositorio(directorioPartidas), advertenciasConfig(advertenciasConfig) {}

const Configuracion& GestorPartidas::getConfiguracion() const { return config; }
const std::vector<std::string>& GestorPartidas::getAdvertenciasConfig() const { return advertenciasConfig; }
const std::string& GestorPartidas::getUltimoError() const { return ultimoError; }

Partida* GestorPartidas::nuevaPartida(const std::string& nombreJugador, int idIA) const
{
    return FabricaPartida::crearNueva(nombreJugador, idIA, config);
}

bool GestorPartidas::guardar(const Partida& partida, const std::string& nombre)
{
    if (!repositorio.guardar(nombre, partida.exportar())) {
        ultimoError = repositorio.getUltimoError();
        return false;
    }
    return true;
}

Partida* GestorPartidas::cargar(const std::string& nombre)
{
    PartidaGuardada estado{};
    if (!repositorio.cargar(nombre, estado)) {
        ultimoError = repositorio.getUltimoError();
        return nullptr;
    }

    try {
        return FabricaPartida::crearDesdeEstado(estado, config);
    } catch (const std::exception& e) {
        ultimoError = std::string("La partida guardada es inválida: ") + e.what();
        return nullptr;
    }
}

std::vector<std::string> GestorPartidas::listarPartidas() const
{
    return repositorio.listar();
}
