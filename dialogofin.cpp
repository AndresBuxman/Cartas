#include "dialogofin.h"
#include "partida.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

DialogoFin::DialogoFin(const Partida &partida, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Fin de la partida");
    setModal(true);

    const Jugador *ganador = partida.getGanador();

    QLabel *titulo = new QLabel(QString("🏆 ¡Ganó %1!").arg(QString::fromStdString(ganador->getNombre())));
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size:22px; font-weight:bold;");

    QLabel *turnos = new QLabel(QString("La partida duró %1 ronda(s).").arg(partida.getTurno()));
    turnos->setAlignment(Qt::AlignCenter);

    QLabel *resumenJugador = new QLabel(resumenDe(partida.getJugador()));
    QLabel *resumenIA = new QLabel(resumenDe(partida.getIA()));
    resumenJugador->setTextFormat(Qt::RichText);
    resumenIA->setTextFormat(Qt::RichText);

    QHBoxLayout *resumenes = new QHBoxLayout;
    resumenes->addWidget(resumenJugador);
    resumenes->addSpacing(30);
    resumenes->addWidget(resumenIA);

    QPushButton *btnNueva = new QPushButton("Nueva partida");
    QPushButton *btnSalir = new QPushButton("Salir del juego");
    connect(btnNueva, &QPushButton::clicked, this, [this] { done(NuevaPartida); });
    connect(btnSalir, &QPushButton::clicked, this, [this] { done(Salir); });

    QHBoxLayout *botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(btnNueva);
    botones->addWidget(btnSalir);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titulo);
    layout->addWidget(turnos);
    layout->addSpacing(10);
    layout->addLayout(resumenes);
    layout->addSpacing(10);
    layout->addLayout(botones);
}

QString DialogoFin::resumenDe(const Jugador *jugador)
{
    QString html = QString("<b>%1</b><br>Elementos restantes: <b>%2</b> de %3<br><br>")
                       .arg(QString::fromStdString(jugador->getNombre()))
                       .arg(jugador->getElementosVivos().size())
                       .arg(jugador->cantidadElementos());

    for (const Elemento *e : jugador->getElementos()) {
        const QString nombre = QString::fromStdString(e->getNombre());
        html += e->estaVivo()
                    ? QString("%1: %2%<br>").arg(nombre).arg(QString::number(e->getEnergia(), 'f', 0))
                    : QString("<span style='color:#888'>%1: fuera de combate</span><br>").arg(nombre);
    }
    return html;
}
