#ifndef DIALOGOFIN_H
#define DIALOGOFIN_H

#include <QDialog>

class Partida;
class Jugador;

// Pantalla de fin de partida: ganador, resumen de elementos y energias finales,
// y opcion de nueva partida o salir.
class DialogoFin : public QDialog
{
    Q_OBJECT

public:
    enum Opcion { NuevaPartida = 1, Salir = 2 };

    explicit DialogoFin(const Partida &partida, QWidget *parent = nullptr);

private:
    static QString resumenDe(const Jugador *jugador);
};

#endif // DIALOGOFIN_H
