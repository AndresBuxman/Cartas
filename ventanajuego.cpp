#include "ventanajuego.h"

#include "cartaelemento.h"
#include "dialogofin.h"
#include "fabricaia.h"
#include "gestorpartidas.h"
#include "partida.h"

#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

VentanaJuego::VentanaJuego(Partida *partida, GestorPartidas *gestor, QWidget *parent)
    : QMainWindow(parent),
      partida(partida),
      gestor(gestor),
      elementoSeleccionado(nullptr)
{
    setWindowTitle("Agua · Tierra · Fuego");
    resize(900, 640);
    construirInterfaz();

    crearCartas(partida->getIA(), layoutIA, cartasIA, false);
    crearCartas(partida->getJugador(), layoutJugador, cartasJugador, true);

    // Partida cargada: se vuelve a marcar el elemento que estaba en juego.
    Elemento *activo = partida->getJugador()->getElementoActivo();
    if (partida->getTurno() > 0 && activo && activo->estaVivo())
        elementoSeleccionado = activo;

    if (partida->getTurno() > 0)
        registroCombate->appendPlainText(
            QString("— Partida reanudada en la ronda %1 —").arg(partida->getTurno() + 1));
    else
        registroCombate->appendPlainText("— Elegí un elemento y presioná “Atacar” —");

    actualizarPantalla();
}

VentanaJuego::~VentanaJuego()
{
    delete partida;
}

void VentanaJuego::construirInterfaz()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    lblTitulo = new QLabel(central);
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setStyleSheet("font-size:15px;");

    lblEnfrentamiento = new QLabel(central);
    lblEnfrentamiento->setAlignment(Qt::AlignCenter);
    lblEnfrentamiento->setStyleSheet("font-weight:bold;");

    QGroupBox *grupoIA = new QGroupBox(
        QString::fromStdString(partida->getIA()->getNombre()) + " — " +
        QString::fromStdString(FabricaIA::nombreVisible(partida->getIA()->getIdIA())), central);
    layoutIA = new QHBoxLayout(grupoIA);
    layoutIA->setSpacing(12);

    QGroupBox *grupoJugador = new QGroupBox(
        QString::fromStdString(partida->getJugador()->getNombre()) + " (vos)", central);
    layoutJugador = new QHBoxLayout(grupoJugador);
    layoutJugador->setSpacing(12);

    registroCombate = new QPlainTextEdit(central);
    registroCombate->setReadOnly(true);
    registroCombate->setMaximumHeight(150);

    btnAtacar = new QPushButton("⚔  Atacar", central);
    btnAtacar->setMinimumHeight(36);
    btnGuardar = new QPushButton("💾  Guardar partida", central);
    btnGuardar->setMinimumHeight(36);
    connect(btnAtacar, &QPushButton::clicked, this, &VentanaJuego::atacar);
    connect(btnGuardar, &QPushButton::clicked, this, &VentanaJuego::guardarPartida);

    QHBoxLayout *botones = new QHBoxLayout;
    botones->addStretch();
    botones->addWidget(btnAtacar);
    botones->addWidget(btnGuardar);
    botones->addStretch();

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(lblTitulo);
    layout->addWidget(grupoIA);
    layout->addWidget(lblEnfrentamiento);
    layout->addWidget(grupoJugador);
    layout->addWidget(registroCombate);
    layout->addLayout(botones);

    QMenu *menu = menuBar()->addMenu("&Partida");
    QAction *accionGuardar = menu->addAction("&Guardar partida");
    accionGuardar->setShortcut(QKeySequence::Save);
    QAction *accionNueva = menu->addAction("&Nueva partida");
    menu->addSeparator();
    QAction *accionSalir = menu->addAction("&Salir");
    connect(accionGuardar, &QAction::triggered, this, &VentanaJuego::guardarPartida);
    connect(accionNueva, &QAction::triggered, this, &VentanaJuego::pedirNuevaPartida);
    connect(accionSalir, &QAction::triggered, qApp, &QApplication::quit);
}

void VentanaJuego::crearCartas(const Jugador *jugador, QHBoxLayout *destino,
                               std::vector<CartaElemento*> &lista, bool seleccionable)
{
    for (Elemento *elemento : jugador->getElementos()) {
        CartaElemento *carta = new CartaElemento(elemento, seleccionable);
        if (seleccionable)
            connect(carta, &CartaElemento::cartaSeleccionada, this, &VentanaJuego::seleccionarCarta);
        lista.push_back(carta);
        destino->addWidget(carta);
    }
    destino->addStretch();
}

void VentanaJuego::seleccionarCarta(CartaElemento *carta)
{
    elementoSeleccionado = carta->getElemento();
    actualizarPantalla();
}

void VentanaJuego::actualizarPantalla()
{
    if (elementoSeleccionado && !elementoSeleccionado->estaVivo())
        elementoSeleccionado = nullptr;

    Elemento *activoIA = partida->getIA()->getElementoActivo();

    for (CartaElemento *carta : cartasJugador) {
        carta->actualizar();
        carta->setMarca(carta->getElemento() == elementoSeleccionado ? "#d00000" : "");
    }
    for (CartaElemento *carta : cartasIA) {
        carta->actualizar();
        const bool enJuego = carta->getElemento() == activoIA && activoIA->estaVivo();
        carta->setMarca(enJuego ? "#0050d0" : "");
    }

    lblTitulo->setText(QString("Ronda <b>%1</b>  —  elementos vivos:  vos <b>%2</b>  |  CPU <b>%3</b>")
                           .arg(partida->getTurno() + 1)
                           .arg(partida->getJugador()->getElementosVivos().size())
                           .arg(partida->getIA()->getElementosVivos().size()));

    lblEnfrentamiento->setText(QString("Tu elemento: %1     |     Elemento de la IA: %2")
        .arg(elementoSeleccionado ? QString::fromStdString(elementoSeleccionado->getNombre()) : "—",
             (activoIA && activoIA->estaVivo()) ? QString::fromStdString(activoIA->getNombre()) : "—"));
}

void VentanaJuego::registrar(const std::vector<ResultadoAtaque> &resultados)
{
    registroCombate->appendPlainText(QString("— Ronda %1 —").arg(partida->getTurno()));
    for (const ResultadoAtaque &r : resultados)
        registroCombate->appendPlainText("  " + QString::fromStdString(r.descripcion()));
}

void VentanaJuego::atacar()
{
    if (!elementoSeleccionado) {
        QMessageBox::information(this, "Atención", "Seleccioná uno de tus elementos para atacar.");
        return;
    }
    if (!partida->setElementoActivoJugador(elementoSeleccionado)) {
        QMessageBox::warning(this, "Atención", "Ese elemento ya no puede combatir.");
        return;
    }

    registrar(partida->ejecutarRonda());
    actualizarPantalla();
    finalizarSiCorresponde();
}

void VentanaJuego::finalizarSiCorresponde()
{
    if (!partida->hayGanador())
        return;

    btnAtacar->setEnabled(false);
    btnGuardar->setEnabled(false);
    registroCombate->appendPlainText(
        QString("★ Fin de la partida: ganó %1").arg(QString::fromStdString(partida->getGanador()->getNombre())));

    DialogoFin dialogo(*partida, this);
    const int opcion = dialogo.exec();

    if (opcion == DialogoFin::Salir) {
        qApp->quit();
        return;
    }
    if (opcion == DialogoFin::NuevaPartida) {
        emit volverAlInicio();
        close();
    }
}

void VentanaJuego::guardarPartida()
{
    if (partida->hayGanador()) {
        QMessageBox::information(this, "Guardar partida", "La partida ya terminó; no hay nada para guardar.");
        return;
    }

    bool aceptado = false;
    const QString sugerido = "partida_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    const QString nombre = QInputDialog::getText(this, "Guardar partida", "Nombre de la partida:",
                                                 QLineEdit::Normal, sugerido, &aceptado).trimmed();
    if (!aceptado || nombre.isEmpty())
        return;

    if (gestor->guardar(*partida, nombre.toStdString()))
        QMessageBox::information(this, "Guardar partida",
                                 QString("Partida «%1» guardada correctamente.").arg(nombre));
    else
        QMessageBox::critical(this, "Error al guardar",
                              "No se pudo guardar la partida:\n" + QString::fromStdString(gestor->getUltimoError()));
}

void VentanaJuego::pedirNuevaPartida()
{
    const auto respuesta = QMessageBox::question(this, "Nueva partida",
        "¿Abandonar la partida actual y volver al inicio?\n(Se perderá el progreso no guardado)");
    if (respuesta == QMessageBox::Yes) {
        emit volverAlInicio();
        close();
    }
}
