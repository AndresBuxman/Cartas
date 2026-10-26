#ifndef ESTADOGUARDADO_H
#define ESTADOGUARDADO_H

#include <type_traits>

// ---------------------------------------------------------------------------
// Structs planos (POD) que representan una partida EN DISCO.
// Flujo de guardado:   clase del juego -> struct -> RepositorioPartidas -> archivo
// Flujo de carga:      archivo -> RepositorioPartidas -> struct -> clase del juego
// Son planos a proposito (sin std::string ni punteros) para poder escribirse
// de una vez como bloque binario. El resto del sistema NUNCA usa estos structs
// para la logica del juego: solo sirven de formato de intercambio.
// ---------------------------------------------------------------------------

constexpr int MAX_ELEMENTOS = 16;        // tope de elementos por jugador
constexpr int MAX_NOMBRE    = 32;        // incluye el '\0'
constexpr int MAGIC_PARTIDA = 0x4F4F5054; // "TPOO": identifica nuestros archivos
constexpr int VERSION_PARTIDA = 1;

struct ElementoGuardado {
    int   id;        // IdElemento
    float energia;   // 0..100
};

struct PartidaGuardada {
    int  magic;
    int  version;
    char nombreJugador[MAX_NOMBRE];
    int  idIA;                                  // IdIA
    int  turno;                                 // rondas jugadas
    int  cantidadJugador;
    ElementoGuardado jugador[MAX_ELEMENTOS];
    int  activoJugador;                         // indice (-1 = ninguno)
    int  cantidadIA;
    ElementoGuardado ia[MAX_ELEMENTOS];
    int  activoIA;                              // indice (-1 = ninguno)
};

static_assert(std::is_trivially_copyable<PartidaGuardada>::value,
              "PartidaGuardada debe poder copiarse byte a byte");

#endif // ESTADOGUARDADO_H
