#include "fabricaelementos.h"

#include <cstdlib>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "idelemento.h"
#include "agua.h"
#include "tierra.h"
#include "fuego.h"
#include "elementosmixtos.h"

namespace {

using Constructor = std::function<Elemento*()>;

const std::map<int, Constructor>& registro()
{
    static const std::map<int, Constructor> tabla = {
        {ID_AGUA,   [] { return static_cast<Elemento*>(new Agua()); }},
        {ID_TIERRA, [] { return static_cast<Elemento*>(new Tierra()); }},
        {ID_FUEGO,  [] { return static_cast<Elemento*>(new Fuego()); }},
        {ID_BARRO,  [] { return static_cast<Elemento*>(new Barro()); }},
        {ID_LAVA,   [] { return static_cast<Elemento*>(new Lava()); }},
        {ID_VAPOR,  [] { return static_cast<Elemento*>(new Vapor()); }}
    };
    return tabla;
}

} // namespace

Elemento* FabricaElementos::crear(int id)
{
    auto it = registro().find(id);
    if (it == registro().end())
        throw std::invalid_argument("Id de elemento desconocido: " + std::to_string(id));
    return it->second();
}

Elemento* FabricaElementos::crearAleatorio(bool incluirMixtos)
{
    std::vector<int> candidatos = {ID_AGUA, ID_TIERRA, ID_FUEGO};
    if (incluirMixtos)
        candidatos.insert(candidatos.end(), {ID_BARRO, ID_LAVA, ID_VAPOR});

    return crear(candidatos[static_cast<size_t>(std::rand()) % candidatos.size()]);
}
