#include "iaaleatoria.h"
#include "idia.h"
#include <cstdlib>

Elemento* IAAleatoria::seleccionarIA(const std::vector<Elemento*>& propios,
                                     const Elemento*, const TablaDanio&)
{
    if (propios.empty()) return nullptr;
    return propios[static_cast<size_t>(std::rand()) % propios.size()];
}

int IAAleatoria::getId() const { return ID_IA_ALEATORIA; }
