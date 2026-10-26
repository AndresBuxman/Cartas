#ifndef REPOSITORIOPARTIDAS_H
#define REPOSITORIOPARTIDAS_H

#include <string>
#include <vector>
#include "estadoguardado.h"

// Unica clase que toca archivos de partidas. Solo conoce el struct PartidaGuardada:
// no sabe nada de Elemento, Jugador, Partida ni de la interfaz.
// Formato: un bloque binario con el struct completo, en <directorio>/<nombre>.sav
class RepositorioPartidas {
private:
    std::string directorio;
    mutable std::string ultimoError;

    std::string rutaDe(const std::string& nombre) const;
    static std::string sanitizar(const std::string& nombre);
    static bool esValido(const PartidaGuardada& estado, std::string& motivo);

public:
    explicit RepositorioPartidas(const std::string& directorio);

    bool guardar(const std::string& nombre, const PartidaGuardada& estado) const;
    bool cargar(const std::string& nombre, PartidaGuardada& destino) const;
    std::vector<std::string> listar() const;

    const std::string& getUltimoError() const;
};

#endif // REPOSITORIOPARTIDAS_H
