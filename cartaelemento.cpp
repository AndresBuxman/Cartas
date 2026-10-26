#include "cartaelemento.h"
#include "elemento.h"
#include "tipoelemento.h"

#include <map>
#include <QLabel>
#include <QMouseEvent>
#include <QProgressBar>
#include <QVBoxLayout>

namespace {

const QString& colorDeTipo(TipoElemento tipo)
{
    static const std::map<TipoElemento, QString> colores = {
        {TipoElemento::AGUA,   "#cfe8ff"},
        {TipoElemento::TIERRA, "#e6d3b3"},
        {TipoElemento::FUEGO,  "#ffd6c9"}
    };
    return colores.at(tipo);
}

} // namespace

CartaElemento::CartaElemento(Elemento *elemento, bool seleccionable, QWidget *parent)
    : QFrame(parent), elemento(elemento), seleccionable(seleccionable)
{
    setObjectName("carta");
    setFixedSize(150, 136);

    lblNombre = new QLabel(this);
    lblNombre->setAlignment(Qt::AlignCenter);
    lblNombre->setStyleSheet("font-weight:bold; font-size:14px; background:transparent;");

    lblTipos = new QLabel(this);
    lblTipos->setAlignment(Qt::AlignCenter);
    lblTipos->setStyleSheet("font-size:10px; background:transparent;");

    barra = new QProgressBar(this);
    barra->setRange(0, 100);
    barra->setAlignment(Qt::AlignCenter);

    lblEstado = new QLabel(this);
    lblEstado->setAlignment(Qt::AlignCenter);
    lblEstado->setStyleSheet("color:#b00000; font-weight:bold; font-size:11px; background:transparent;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->setSpacing(3);
    layout->addWidget(lblNombre);
    layout->addWidget(lblTipos);
    layout->addWidget(barra);
    layout->addWidget(lblEstado);

    setCursor(seleccionable ? Qt::PointingHandCursor : Qt::ArrowCursor);
    actualizar();
}

Elemento* CartaElemento::getElemento() const
{
    return elemento;
}

void CartaElemento::actualizar()
{
    lblNombre->setText(QString::fromStdString(elemento->getNombre()));
    lblTipos->setText(QString("Ataca: %1\nDefiende: %2")
                          .arg(QString::fromStdString(TiposElemento::aTexto(elemento->getTipoAtaque())),
                               QString::fromStdString(TiposElemento::aTexto(elemento->getTipoDefensa()))));

    const float energia = elemento->getEnergia();
    barra->setValue(qRound(energia));
    barra->setFormat(QString("%1%").arg(QString::number(energia, 'f', energia == qRound(energia) ? 0 : 1)));

    const QString colorBarra = energia > 50.0f ? "#4caf50" : (energia > 25.0f ? "#f0a030" : "#d03030");
    barra->setStyleSheet(QString("QProgressBar{border:1px solid #666; border-radius:3px; background:white; height:16px;}"
                                 "QProgressBar::chunk{background:%1;}").arg(colorBarra));

    lblEstado->setText(elemento->estaVivo() ? QString(" ") : QString("FUERA DE COMBATE"));
    refrescarEstilo();
}

void CartaElemento::setMarca(const QString &colorBorde)
{
    marca = colorBorde;
    refrescarEstilo();
}

void CartaElemento::refrescarEstilo()
{
    const QString fondo = elemento->estaVivo() ? colorDeTipo(elemento->getTipoAtaque()) : QString("#cfcfcf");
    const QString borde = marca.isEmpty() ? QString("#666666") : marca;
    const int grosor = marca.isEmpty() ? 1 : 4;

    setStyleSheet(QString("QFrame#carta{background:%1; border:%2px solid %3; border-radius:7px;}")
                      .arg(fondo).arg(grosor).arg(borde));
}

void CartaElemento::mousePressEvent(QMouseEvent *event)
{
    if (seleccionable && elemento->estaVivo())
        emit cartaSeleccionada(this);

    QFrame::mousePressEvent(event);
}
