#include "tipoelemento.h"

#include <algorithm>
#include <cctype>
#include <map>
#include <stdexcept>

namespace {

const std::map<TipoElemento, std::string>& nombres()
{
    static const std::map<TipoElemento, std::string> tabla = {
        {TipoElemento::AGUA,   "Agua"},
        {TipoElemento::TIERRA, "Tierra"},
        {TipoElemento::FUEGO,  "Fuego"}
    };
    return tabla;
}

std::string aMayusculas(std::string texto)
{
    std::transform(texto.begin(), texto.end(), texto.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return texto;
}

} // namespace

std::string TiposElemento::aTexto(TipoElemento tipo)
{
    return nombres().at(tipo);
}

TipoElemento TiposElemento::desdeTexto(const std::string& texto)
{
    const std::string buscado = aMayusculas(texto);
    for (const auto& par : nombres()) {
        if (aMayusculas(par.second) == buscado)
            return par.first;
    }
    throw std::invalid_argument("Tipo de elemento desconocido: " + texto);
}
