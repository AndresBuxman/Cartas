#ifndef RESULTADOATAQUE_H
#define RESULTADOATAQUE_H

#include <string>

// Datos de un ataque ya realizado (quien, a quien, cuanto, si lo elimino).
// La interfaz los usa para mostrar el resultado de cada enfrentamiento.
class ResultadoAtaque {
private:
    std::string duenioAtacante;
    std::string elementoAtacante;
    std::string duenioDefensor;
    std::string elementoDefensor;
    float danio;
    bool eliminado;

public:
    ResultadoAtaque(const std::string& duenioAtacante, const std::string& elementoAtacante,
                    const std::string& duenioDefensor, const std::string& elementoDefensor,
                    float danio, bool eliminado);

    const std::string& getDuenioAtacante() const;
    const std::string& getElementoAtacante() const;
    const std::string& getDuenioDefensor() const;
    const std::string& getElementoDefensor() const;
    float getDanio() const;
    bool fueEliminado() const;

    std::string descripcion() const;
};

#endif // RESULTADOATAQUE_H
