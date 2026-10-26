#include "ventanainicio.h"

#include "fabricaia.h"
#include "gestorpartidas.h"
#include "ventanajuego.h"

#include <QComboBox>
#include <QFormLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

VentanaInicio::VentanaInicio(GestorPartidas *gestor, QWidget *parent)
    : QWidget(parent), gestor(gestor)
{
    setWindowTitle("Agua · Tierra · Fuego");
    setMinimumWidth(380);

    QLabel *titulo = new QLabel("💧 Agua  ·  🌱 Tierra  ·  🔥 Fuego");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size:20px; font-weight:bold;");

    txtNombre = new QLineEdit("Jugador");
    txtNombre->setMaxLength(24);

    // Los items salen de la fabrica: el id de cada IA queda guardado en el item.
    cmbIA = new QComboBox;
    for (int id : FabricaIA::ids())
        cmbIA->addItem(QString::fromStdString(FabricaIA::nombreVisible(id)), id);
    cmbIA->setCurrentIndex(cmbIA->findData(gestor->getConfiguracion().getIdIA()));

    QFormLayout *formulario = new QFormLayout;
    formulario->addRow("Tu nombre:", txtNombre);
    formulario->addRow("Oponente (IA):", cmbIA);

    QLabel *info = new QLabel(QString("Elementos por jugador: %1%2")
        .arg(gestor->getConfiguracion().getCantidadElementos())
        .arg(gestor->getConfiguracion().getElementosMixtos() ? "  (con elementos mixtos)" : ""));
    info->setStyleSheet("color:#555;");
    info->setAlignment(Qt::AlignCenter);

    QPushButton *btnNueva = new QPushButton("Nueva partida");
    QPushButton *btnCargar = new QPushButton("Cargar partida guardada");
    QPushButton *btnSalir = new QPushButton("Salir");
    btnNueva->setMinimumHeight(34);
    btnCargar->setMinimumHeight(34);
    connect(btnNueva, &QPushButton::clicked, this, &VentanaInicio::nuevaPartida);
    connect(btnCargar, &QPushButton::clicked, this, &VentanaInicio::cargarPartida);
    connect(btnSalir, &QPushButton::clicked, this, &QWidget::close);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titulo);
    layout->addSpacing(8);
    layout->addLayout(formulario);
    layout->addWidget(info);
    layout->addSpacing(6);
    layout->addWidget(btnNueva);
    layout->addWidget(btnCargar);
    layout->addWidget(btnSalir);

    // Si config.txt tuvo lineas invalidas se informa, sin frenar el juego.
    const auto &advertencias = gestor->getAdvertenciasConfig();
    if (!advertencias.empty()) {
        QStringList lineas;
        for (const std::string &a : advertencias)
            lineas << QString::fromStdString(a);
        QLabel *aviso = new QLabel("⚠ Configuración: " + lineas.join("\n"));
        aviso->setStyleSheet("color:#a05a00; font-size:11px;");
        aviso->setWordWrap(true);
        layout->addWidget(aviso);
    }
}

void VentanaInicio::nuevaPartida()
{
    Partida *partida = gestor->nuevaPartida(txtNombre->text().trimmed().toStdString(),
                                            cmbIA->currentData().toInt());
    abrirJuego(partida);
}

void VentanaInicio::cargarPartida()
{
    QStringList nombres;
    for (const std::string &n : gestor->listarPartidas())
        nombres << QString::fromStdString(n);

    if (nombres.isEmpty()) {
        QMessageBox::information(this, "Cargar partida", "No hay partidas guardadas todavía.");
        return;
    }

    bool aceptado = false;
    const QString elegido = QInputDialog::getItem(this, "Cargar partida", "Partidas guardadas:",
                                                  nombres, 0, false, &aceptado);
    if (!aceptado)
        return;

    Partida *partida = gestor->cargar(elegido.toStdString());
    if (!partida) {
        QMessageBox::critical(this, "Error al cargar",
                              "No se pudo cargar la partida:\n" + QString::fromStdString(gestor->getUltimoError()));
        return;
    }
    abrirJuego(partida);
}

void VentanaInicio::abrirJuego(Partida *partida)
{
    VentanaJuego *ventana = new VentanaJuego(partida, gestor);
    ventana->setAttribute(Qt::WA_DeleteOnClose);
    connect(ventana, &VentanaJuego::volverAlInicio, this, [this] { show(); });
    ventana->show();
    hide();
}
