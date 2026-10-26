#ifndef FABRICAIA_H
#define FABRICAIA_H

#include <string>
#include <vector>
#include "ia.h"

// Crea IAs por id y traduce nombres. Usa un registro, sin switch.
class FabricaIA
{
public:
    // Lanza std::invalid_argument si el id no existe.
    static IA* crear(int id);
    // Convierte "ALEATORIA" / "ESTRATEGICA" / "SUPERIA" (config.txt) en id.
    // Lanza std::invalid_argument si no se reconoce.
    static int idDesdeClave(const std::string& clave);
    // Texto para mostrar al usuario ("Super IA", etc.).
    static std::string nombreVisible(int id);
    // Ids disponibles, en orden.
    static std::vector<int> ids();
};

#endif // FABRICAIA_H
