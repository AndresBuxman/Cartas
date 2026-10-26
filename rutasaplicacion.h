#ifndef RUTASAPLICACION_H
#define RUTASAPLICACION_H

#include <string>

// Decide en que carpeta viven config.txt y partidas/.
// Prueba: carpeta actual, la del ejecutable (y hasta 3 niveles arriba) y, si el
// .pro la definio, la carpeta del proyecto. Asi funciona tanto desde Qt Creator
// (build en otra carpeta) como ejecutando el .exe junto a config.txt.
class RutasAplicacion
{
public:
    static std::string directorioBase(const std::string& directorioEjecutable);
};

#endif // RUTASAPLICACION_H
