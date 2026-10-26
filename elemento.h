#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <string>
#include "tipoelemento.h"
#include "estadoguardado.h"

class TablaDanio;

// Clase base de todos los elementos. No se instancia directamente
// (constructor protegido): se usan Agua, Tierra, Fuego y los mixtos.
class Elemento {
protected:
    std::string nombre;
    int id;                 // IdElemento de la clase concreta
    float energia;          // 0..100
    TipoElemento tipo;      // tipo con el que ataca

    Elemento(const std::string& nombre, int id, TipoElemento tipo, float energiaInicial = 100.0f);

public:
    virtual ~Elemento() = default;

    // Polimorfismo: el daño sale de la tabla segun el tipo de ataque y de defensa.
    virtual void atacar(Elemento& objetivo, const TablaDanio& tabla);
    virtual void recibirDanio(float danio);
    virtual TipoElemento getTipoAtaque() const;
    virtual TipoElemento getTipoDefensa() const;

    const std::string& getNombre() const;
    int getId() const;
    float getEnergia() const;
    bool estaVivo() const;

    // Persistencia: clase -> struct (la lectura/escritura del archivo NO esta aqui).
    ElementoGuardado exportar() const;
    void restaurarEnergia(float valor);
};

#endif // ELEMENTO_H
