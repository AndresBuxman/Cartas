#include "superia.h"
#include "idia.h"

Elemento* SuperIA::seleccionarIA(const std::vector<Elemento*>& propios,
                                 const Elemento* oponenteActivo,
                                 const TablaDanio& tabla)
{
    if (propios.empty()) return nullptr;
    if (!oponenteActivo) return propios.front();

    Elemento* elegido = nullptr;
    for (Elemento* candidato : propios) {
        bool remata = tabla.getDanio(*candidato, *oponenteActivo) >= oponenteActivo->getEnergia();
        if (remata && (elegido == nullptr || candidato->getEnergia() < elegido->getEnergia()))
            elegido = candidato;
    }

    return elegido ? elegido : mejorPorVentaja(propios, *oponenteActivo, tabla);
}

int SuperIA::getId() const { return ID_IA_SUPERIA; }
