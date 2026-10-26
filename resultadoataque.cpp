#include "resultadoataque.h"

#include <sstream>

ResultadoAtaque::ResultadoAtaque(const std::string& duenioAtacante, const std::string& elementoAtacante,
                                 const std::string& duenioDefensor, const std::string& elementoDefensor,
                                 float danio, bool eliminado)
    : duenioAtacante(duenioAtacante), elementoAtacante(elementoAtacante),
      duenioDefensor(duenioDefensor), elementoDefensor(elementoDefensor),
      danio(danio), eliminado(eliminado) {}

const std::string& ResultadoAtaque::getDuenioAtacante() const  { return duenioAtacante; }
const std::string& ResultadoAtaque::getElementoAtacante() const { return elementoAtacante; }
const std::string& ResultadoAtaque::getDuenioDefensor() const  { return duenioDefensor; }
const std::string& ResultadoAtaque::getElementoDefensor() const { return elementoDefensor; }
float ResultadoAtaque::getDanio() const { return danio; }
bool ResultadoAtaque::fueEliminado() const { return eliminado; }

std::string ResultadoAtaque::descripcion() const
{
    std::ostringstream texto;
    texto << duenioAtacante << " (" << elementoAtacante << ") atacó a "
          << duenioDefensor << " (" << elementoDefensor << "): -" << danio << "% de energía.";
    if (eliminado)
        texto << " ¡" << elementoDefensor << " de " << duenioDefensor << " quedó fuera de combate!";
    return texto.str();
}
