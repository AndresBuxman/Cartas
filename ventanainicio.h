#ifndef VENTANAINICIO_H
#define VENTANAINICIO_H

#include <QWidget>

class QComboBox;
class QLineEdit;
class GestorPartidas;
class Partida;

// Pantalla de inicio / configuracion: nombre, tipo de IA, nueva partida o cargar una guardada.
class VentanaInicio : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaInicio(GestorPartidas *gestor, QWidget *parent = nullptr);

private slots:
    void nuevaPartida();
    void cargarPartida();

private:
    void abrirJuego(Partida *partida);

    GestorPartidas *gestor;
    QLineEdit *txtNombre;
    QComboBox *cmbIA;
};

#endif // VENTANAINICIO_H
