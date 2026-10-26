#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QMainWindow>
#include <vector>

#include "resultadoataque.h"

class QHBoxLayout;
class QLabel;
class QPlainTextEdit;
class QPushButton;
class CartaElemento;
class Elemento;
class Jugador;
class Partida;
class GestorPartidas;

// Pantalla de juego. Solo traduce acciones del usuario a llamadas sobre Partida
// y dibuja su estado; las reglas viven en Partida y los archivos en GestorPartidas.
class VentanaJuego : public QMainWindow
{
    Q_OBJECT

public:
    // Toma posesion de 'partida' (la libera al cerrarse). 'gestor' debe sobrevivir a la ventana.
    VentanaJuego(Partida *partida, GestorPartidas *gestor, QWidget *parent = nullptr);
    ~VentanaJuego() override;

signals:
    void volverAlInicio();

private slots:
    void atacar();
    void seleccionarCarta(CartaElemento *carta);
    void guardarPartida();
    void pedirNuevaPartida();

private:
    void construirInterfaz();
    void crearCartas(const Jugador *jugador, QHBoxLayout *destino,
                     std::vector<CartaElemento*> &lista, bool seleccionable);
    void actualizarPantalla();
    void registrar(const std::vector<ResultadoAtaque> &resultados);
    void finalizarSiCorresponde();

    Partida *partida;
    GestorPartidas *gestor;

    Elemento *elementoSeleccionado;
    std::vector<CartaElemento*> cartasJugador;
    std::vector<CartaElemento*> cartasIA;

    QLabel *lblTitulo;
    QLabel *lblEnfrentamiento;
    QPlainTextEdit *registroCombate;
    QPushButton *btnAtacar;
    QPushButton *btnGuardar;
    QHBoxLayout *layoutIA;
    QHBoxLayout *layoutJugador;
};

#endif // VENTANAJUEGO_H
