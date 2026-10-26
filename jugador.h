#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "elemento.h"

// El jugador es dueño de sus elementos y los libera en el destructor.
class Jugador {
protected:
    std::string nombre;
    std::vector<Elemento*> elementos;
    int indiceActivo;   // elemento en combate; -1 si no hay ninguno

public:
    explicit Jugador(const std::string& nombre);
    virtual ~Jugador();

    Jugador(const Jugador&) = delete;
    Jugador& operator=(const Jugador&) = delete;

    void agregarElemento(Elemento* elemento);

    virtual Elemento* seleccionarElemento();

    bool tieneElementosVivos() const;
    const std::vector<Elemento*>& getElementos() const;
    std::vector<Elemento*> getElementosVivos() const;
    int cantidadElementos() const;
    Elemento* getElemento(int indice) const;

    const std::string& getNombre() const;
    Elemento* getElementoActivo() const;
    int getIndiceElementoActivo() const;

    void setIndiceElementoActivo(int indice);       // -1 o un indice valido
    bool setElementoActivo(const Elemento* elemento); // solo si es propio y esta vivo
    void avanzarAlSiguienteVivo();
};

#endif // JUGADOR_H
