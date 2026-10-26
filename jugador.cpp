#include "jugador.h"

Jugador::Jugador(const std::string& nombre) : nombre(nombre), indiceActivo(-1) {}

Jugador::~Jugador()
{
    for (Elemento* e : elementos)
        delete e;
}

void Jugador::agregarElemento(Elemento* elemento)
{
    elementos.push_back(elemento);
    if (indiceActivo == -1 && elemento->estaVivo())
        indiceActivo = static_cast<int>(elementos.size()) - 1;
}

bool Jugador::tieneElementosVivos() const
{
    for (const Elemento* e : elementos) {
        if (e->estaVivo()) return true;
    }
    return false;
}

const std::vector<Elemento*>& Jugador::getElementos() const { return elementos; }

std::vector<Elemento*> Jugador::getElementosVivos() const
{
    std::vector<Elemento*> vivos;
    for (Elemento* e : elementos) {
        if (e->estaVivo()) vivos.push_back(e);
    }
    return vivos;
}

int Jugador::cantidadElementos() const
{
    return static_cast<int>(elementos.size());
}

Elemento* Jugador::getElemento(int indice) const
{
    if (indice < 0 || indice >= cantidadElementos())
        return nullptr;
    return elementos[static_cast<size_t>(indice)];
}

Elemento* Jugador::seleccionarElemento()
{
    return getElementoActivo();
}

const std::string& Jugador::getNombre() const { return nombre; }

Elemento* Jugador::getElementoActivo() const { return getElemento(indiceActivo); }

int Jugador::getIndiceElementoActivo() const { return indiceActivo; }

void Jugador::setIndiceElementoActivo(int indice)
{
    bool valido = indice >= 0 && indice < cantidadElementos();
    indiceActivo = valido ? indice : -1;
}

bool Jugador::setElementoActivo(const Elemento* elemento)
{
    for (int i = 0; i < cantidadElementos(); ++i) {
        if (elementos[static_cast<size_t>(i)] == elemento && elemento->estaVivo()) {
            indiceActivo = i;
            return true;
        }
    }
    return false;
}

void Jugador::avanzarAlSiguienteVivo()
{
    const int n = cantidadElementos();
    for (int paso = 1; paso <= n; ++paso) {
        int i = (indiceActivo + paso) % n;
        if (elementos[static_cast<size_t>(i)]->estaVivo()) {
            indiceActivo = i;
            return;
        }
    }
    indiceActivo = -1;
}
