#ifndef LECTORCONFIGURACION_H
#define LECTORCONFIGURACION_H

#include <string>
#include <vector>
#include "configuracion.h"

// Lee config.txt. Formato: una directiva por linea, "clave valores...".
// '#' inicia un comentario. Si el archivo no existe se usan los valores por
// defecto; las lineas invalidas se ignoran y quedan registradas como advertencias.
class LectorConfiguracion {
private:
    std::vector<std::string> advertencias;

    void procesarLinea(const std::string& linea, int numeroLinea, Configuracion& config);
    void advertir(const std::string& mensaje);

public:
    Configuracion leer(const std::string& ruta);
    const std::vector<std::string>& getAdvertencias() const;
};

#endif // LECTORCONFIGURACION_H
