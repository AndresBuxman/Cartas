#include "fabricaia.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <map>
#include <stdexcept>

#include "idia.h"
#include "iaaleatoria.h"
#include "iaestrategica.h"
#include "superia.h"

namespace {

class Entrada {
private:
    std::string claveConfig;
    std::string nombreMostrado;
    std::function<IA*()> constructor;

public:
    Entrada(const std::string& clave, const std::string& nombre, std::function<IA*()> constructor)
        : claveConfig(clave), nombreMostrado(nombre), constructor(constructor) {}

    const std::string& clave() const { return claveConfig; }
    const std::string& nombre() const { return nombreMostrado; }
    IA* crear() const { return constructor(); }
};

const std::map<int, Entrada>& registro()
{
    static const std::map<int, Entrada> tabla = {
        {ID_IA_ALEATORIA,   {"ALEATORIA",   "IA Aleatoria",   [] { return static_cast<IA*>(new IAAleatoria()); }}},
        {ID_IA_ESTRATEGICA, {"ESTRATEGICA", "IA Estratégica", [] { return static_cast<IA*>(new IAEstrategica()); }}},
        {ID_IA_SUPERIA,     {"SUPERIA",     "Super IA",       [] { return static_cast<IA*>(new SuperIA()); }}}
    };
    return tabla;
}

const Entrada& buscar(int id)
{
    auto it = registro().find(id);
    if (it == registro().end())
        throw std::invalid_argument("Id de IA desconocido: " + std::to_string(id));
    return it->second;
}

} // namespace

IA* FabricaIA::crear(int id)
{
    return buscar(id).crear();
}

int FabricaIA::idDesdeClave(const std::string& clave)
{
    std::string buscado = clave;
    std::transform(buscado.begin(), buscado.end(), buscado.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });

    for (const auto& par : registro()) {
        if (par.second.clave() == buscado)
            return par.first;
    }
    throw std::invalid_argument("Tipo de IA desconocido: " + clave);
}

std::string FabricaIA::nombreVisible(int id)
{
    return buscar(id).nombre();
}

std::vector<int> FabricaIA::ids()
{
    std::vector<int> resultado;
    for (const auto& par : registro())
        resultado.push_back(par.first);
    return resultado;
}
