#ifndef CARTAELEMENTO_H
#define CARTAELEMENTO_H

#include <QFrame>
#include <QString>

class QLabel;
class QProgressBar;
class Elemento;

// Tarjeta visual de un elemento: nombre, tipos, barra de energia y estado.
// Solo MUESTRA el elemento (no lo modifica) y avisa cuando el usuario la elige.
class CartaElemento : public QFrame
{
    Q_OBJECT

public:
    explicit CartaElemento(Elemento *elemento, bool seleccionable, QWidget *parent = nullptr);

    Elemento* getElemento() const;

    void actualizar();                       // relee energia y estado del elemento
    void setMarca(const QString &colorBorde); // "" = sin marca

signals:
    void cartaSeleccionada(CartaElemento *carta);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void refrescarEstilo();

    Elemento *elemento;
    bool seleccionable;
    QString marca;

    QLabel *lblNombre;
    QLabel *lblTipos;
    QProgressBar *barra;
    QLabel *lblEstado;
};

#endif // CARTAELEMENTO_H
