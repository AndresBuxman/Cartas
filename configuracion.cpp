#include "configuracion.h"
#include "idia.h"

Configuracion::Configuracion()
    : cantidadElementos(5),
      idIA(ID_IA_ESTRATEGICA),
      elementosMixtos(false),
      tablaDanio(TablaDanio::porDefecto())
{
}

int Configuracion::getCantidadElementos() const { return cantidadElementos; }
int Configuracion::getIdIA() const { return idIA; }
bool Configuracion::getElementosMixtos() const { return elementosMixtos; }
const TablaDanio& Configuracion::getTablaDanio() const { return tablaDanio; }

void Configuracion::setCantidadElementos(int cantidad) { cantidadElementos = cantidad; }
void Configuracion::setIdIA(int id) { idIA = id; }
void Configuracion::setElementosMixtos(bool incluir) { elementosMixtos = incluir; }

void Configuracion::configurarDanio(TipoElemento atacante, TipoElemento defensor, float danio)
{
    tablaDanio.configurarDanio(atacante, defensor, danio);
}
