#include <QApplication>
#include <QCoreApplication>
#include <cstdlib>
#include <ctime>

#include "gestorpartidas.h"
#include "lectorconfiguracion.h"
#include "rutasaplicacion.h"
#include "ventanainicio.h"

int main(int argc, char *argv[])
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));   // reparto distinto en cada ejecucion

    QApplication app(argc, argv);

    const std::string base = RutasAplicacion::directorioBase(
        QCoreApplication::applicationDirPath().toStdString());

    LectorConfiguracion lector;
    Configuracion config = lector.leer(base + "/config.txt");
    GestorPartidas gestor(config, base + "/partidas", lector.getAdvertencias());

    VentanaInicio ventana(&gestor);
    ventana.show();

    return app.exec();
}
