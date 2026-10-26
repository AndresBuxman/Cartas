#include "tabladanio.h"
#include "elemento.h"

TablaDanio TablaDanio::porDefecto()
{
    TablaDanio t;
    t.configurarDanio(TipoElemento::AGUA,   TipoElemento::FUEGO,  50.0f);
    t.configurarDanio(TipoElemento::FUEGO,  TipoElemento::AGUA,   20.0f);
    t.configurarDanio(TipoElemento::TIERRA, TipoElemento::FUEGO,  20.0f);
    t.configurarDanio(TipoElemento::FUEGO,  TipoElemento::TIERRA, 40.0f);
    t.configurarDanio(TipoElemento::AGUA,   TipoElemento::TIERRA, 30.0f);
    t.configurarDanio(TipoElemento::TIERRA, TipoElemento::AGUA,   50.0f);
    t.configurarDanio(TipoElemento::AGUA,   TipoElemento::AGUA,   15.0f);
    t.configurarDanio(TipoElemento::TIERRA, TipoElemento::TIERRA, 15.0f);
    t.configurarDanio(TipoElemento::FUEGO,  TipoElemento::FUEGO,  15.0f);
    return t;
}

void TablaDanio::configurarDanio(TipoElemento atacante, TipoElemento defensor, float porcentajeDanio)
{
    tabla[Par(atacante, defensor)] = porcentajeDanio;
}

float TablaDanio::getDanio(TipoElemento atacante, TipoElemento defensor) const
{
    auto it = tabla.find(Par(atacante, defensor));
    return (it != tabla.end()) ? it->second : 0.0f;
}

float TablaDanio::getDanio(const Elemento& atacante, const Elemento& defensor) const
{
    return getDanio(atacante.getTipoAtaque(), defensor.getTipoDefensa());
}

bool TablaDanio::tieneRegla(TipoElemento atacante, TipoElemento defensor) const
{
    return tabla.find(Par(atacante, defensor)) != tabla.end();
}

bool TablaDanio::esMayor(float ventajaA, float ventajaB) const
{
    return ventajaA > ventajaB;
}
