#include "elemento.h"
#include "tabladanio.h"

#include <algorithm>

Elemento::Elemento(const std::string& nombre, int id, TipoElemento tipo, float energiaInicial)
    : nombre(nombre), id(id), energia(energiaInicial), tipo(tipo) {}

void Elemento::atacar(Elemento& objetivo, const TablaDanio& tabla)
{
    objetivo.recibirDanio(tabla.getDanio(*this, objetivo));
}

void Elemento::recibirDanio(float danio)
{
    energia = std::max(0.0f, energia - danio);
}

TipoElemento Elemento::getTipoAtaque() const  { return tipo; }
TipoElemento Elemento::getTipoDefensa() const { return tipo; }

const std::string& Elemento::getNombre() const { return nombre; }
int Elemento::getId() const { return id; }
float Elemento::getEnergia() const { return energia; }
bool Elemento::estaVivo() const { return energia > 0.0f; }

ElementoGuardado Elemento::exportar() const
{
    ElementoGuardado datos{};
    datos.id = id;
    datos.energia = energia;
    return datos;
}

void Elemento::restaurarEnergia(float valor)
{
    energia = std::min(100.0f, std::max(0.0f, valor));
}
