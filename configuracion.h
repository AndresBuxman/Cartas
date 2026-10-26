#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "tabladanio.h"

// Parametros del juego. Es un objeto de valores: no lee archivos (eso es
// responsabilidad de LectorConfiguracion). Nace con valores por defecto.
class Configuracion {
private:
    int cantidadElementos;
    int idIA;
    bool elementosMixtos;
    TablaDanio tablaDanio;

public:
    Configuracion();

    int getCantidadElementos() const;
    int getIdIA() const;
    bool getElementosMixtos() const;
    const TablaDanio& getTablaDanio() const;

    void setCantidadElementos(int cantidad);
    void setIdIA(int id);
    void setElementosMixtos(bool incluir);
    void configurarDanio(TipoElemento atacante, TipoElemento defensor, float danio);
};

#endif // CONFIGURACION_H
