#ifndef FABRICAPARTIDA_H
#define FABRICAPARTIDA_H

#include <string>
#include "partida.h"
#include "configuracion.h"
#include "estadoguardado.h"

// Arma partidas: nuevas (elementos al azar) o reconstruidas desde un struct (struct -> clase).
class FabricaPartida
{
public:
    static Partida* crearNueva(const std::string& nombreJugador, int idIA, const Configuracion& config);

    // Lanza std::invalid_argument si el struct referencia ids inexistentes.
    static Partida* crearDesdeEstado(const PartidaGuardada& estado, const Configuracion& config);
};

#endif // FABRICAPARTIDA_H
