#ifndef TIPOELEMENTO_H
#define TIPOELEMENTO_H

#include <string>

// Tipos elementales base. Los mixtos (Barro, Lava, Vapor) combinan dos de estos.
enum class TipoElemento {
    AGUA,
    TIERRA,
    FUEGO
};

// Conversion entre TipoElemento y texto (sin switch: usa una tabla).
class TiposElemento {
public:
    static std::string aTexto(TipoElemento tipo);
    // Acepta mayusculas o minusculas. Lanza std::invalid_argument si no existe.
    static TipoElemento desdeTexto(const std::string& texto);
};

#endif // TIPOELEMENTO_H
