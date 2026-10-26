#ifndef GESTORPARTIDAS_H
#define GESTORPARTIDAS_H

#include <string>
#include <vector>
#include "configuracion.h"
#include "repositoriopartidas.h"
#include "partida.h"

// Punto de entrada que usa la interfaz: une configuracion, fabrica y repositorio
// para que la UI no tenga que conocer ni archivos ni constructores.
class GestorPartidas
{
private:
    Configuracion config;
    RepositorioPartidas repositorio;
    std::vector<std::string> advertenciasConfig;
    std::string ultimoError;

public:
    GestorPartidas(const Configuracion& config, const std::string& directorioPartidas,
                   const std::vector<std::string>& advertenciasConfig = {});

    const Configuracion& getConfiguracion() const;
    const std::vector<std::string>& getAdvertenciasConfig() const;

    // El que llama es dueño de la Partida devuelta.
    Partida* nuevaPartida(const std::string& nombreJugador, int idIA) const;
    Partida* cargar(const std::string& nombre);          // nullptr si falla
    bool guardar(const Partida& partida, const std::string& nombre);
    std::vector<std::string> listarPartidas() const;

    const std::string& getUltimoError() const;
};

#endif // GESTORPARTIDAS_H
