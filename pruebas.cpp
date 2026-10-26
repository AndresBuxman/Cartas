// Pruebas de consola de la logica, la configuracion y la persistencia (sin Qt).
// Uso:  pruebas            -> corre las pruebas
//       pruebas --ejemplo <carpeta_partidas>   -> ademas genera partidas/ejemplo.sav
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <filesystem>

#include "agua.h"
#include "tierra.h"
#include "fuego.h"
#include "elementosmixtos.h"
#include "idia.h"
#include "idelemento.h"
#include "fabricaelementos.h"
#include "fabricaia.h"
#include "fabricapartida.h"
#include "gestorpartidas.h"
#include "lectorconfiguracion.h"
#include "repositoriopartidas.h"

namespace fs = std::filesystem;

static int fallos = 0, total = 0;
#define VERIFICAR(cond) do { ++total; if (!(cond)) { ++fallos; \
    std::cout << "  [FALLA] " #cond "  (linea " << __LINE__ << ")\n"; } } while (0)

static void escribirArchivo(const std::string& ruta, const std::string& texto)
{
    std::ofstream(ruta) << texto;
}

static void pruebaCombate()
{
    std::cout << "- Combate y reglas\n";
    TablaDanio t = TablaDanio::porDefecto();

    Agua agua; Fuego fuego; Tierra tierra;
    agua.atacar(fuego, t);
    VERIFICAR(fuego.getEnergia() == 50.0f);

    // Un elemento mixto ataca con un tipo y se defiende con otro.
    Barro barro;                       // ataca AGUA, defiende TIERRA
    VERIFICAR(barro.getTipoAtaque() == TipoElemento::AGUA);
    VERIFICAR(barro.getTipoDefensa() == TipoElemento::TIERRA);
    Fuego f2; f2.atacar(barro, t);     // FUEGO -> TIERRA = 40
    VERIFICAR(barro.getEnergia() == 60.0f);
    Vapor vapor; Lava lava;
    VERIFICAR(vapor.getTipoAtaque() == TipoElemento::FUEGO && vapor.getTipoDefensa() == TipoElemento::AGUA);
    VERIFICAR(lava.getTipoAtaque() == TipoElemento::FUEGO && lava.getTipoDefensa() == TipoElemento::TIERRA);

    // La energia nunca baja de 0.
    Fuego casiMuerto(10.0f);
    agua.atacar(casiMuerto, t);
    VERIFICAR(casiMuerto.getEnergia() == 0.0f && !casiMuerto.estaVivo());

    // Ronda: el elemento eliminado NO contraataca.
    Jugador* h = new Jugador("Ana");
    h->agregarElemento(new Agua());
    IAJugador* c = new IAJugador("CPU", FabricaIA::crear(ID_IA_ALEATORIA));
    c->agregarElemento(new Fuego(30.0f));
    Partida p(h, c, t);
    VERIFICAR(p.setElementoActivoJugador(h->getElemento(0)));
    auto r = p.ejecutarRonda();
    VERIFICAR(r.size() == 1);
    VERIFICAR(r[0].fueEliminado());
    VERIFICAR(h->getElemento(0)->getEnergia() == 100.0f);
    VERIFICAR(p.hayGanador() && p.getGanador() == h);
    VERIFICAR(p.ejecutarRonda().empty());   // terminada: no se juega mas
}

static void pruebaFabricas()
{
    std::cout << "- Fabricas\n";
    bool lanzo = false;
    try { FabricaElementos::crear(999); } catch (const std::invalid_argument&) { lanzo = true; }
    VERIFICAR(lanzo);
    lanzo = false;
    try { FabricaIA::crear(999); } catch (const std::invalid_argument&) { lanzo = true; }
    VERIFICAR(lanzo);

    for (int i = 0; i < 200; ++i) {
        std::unique_ptr<Elemento> e(FabricaElementos::crearAleatorio(false));
        VERIFICAR(e->getId() <= ID_FUEGO);
    }
    VERIFICAR(FabricaIA::idDesdeClave("superia") == ID_IA_SUPERIA);
    VERIFICAR(FabricaIA::ids().size() == 3);
}

static void pruebaConfiguracion(const std::string& tmp)
{
    std::cout << "- Configuracion\n";
    LectorConfiguracion lector;

    Configuracion porDefecto = lector.leer(tmp + "/no_existe.txt");   // archivo inexistente
    VERIFICAR(porDefecto.getCantidadElementos() == 5);
    VERIFICAR(lector.getAdvertencias().size() == 1);

    escribirArchivo(tmp + "/cfg_ok.txt",
        "# comentario\n"
        "cantidad_elementos 3   # inline\n"
        "ia ALEATORIA\n"
        "elementos_mixtos 1\n"
        "danio AGUA FUEGO 77\n");
    Configuracion ok = lector.leer(tmp + "/cfg_ok.txt");
    VERIFICAR(ok.getCantidadElementos() == 3);
    VERIFICAR(ok.getIdIA() == ID_IA_ALEATORIA);
    VERIFICAR(ok.getElementosMixtos());
    VERIFICAR(ok.getTablaDanio().getDanio(TipoElemento::AGUA, TipoElemento::FUEGO) == 77.0f);
    VERIFICAR(ok.getTablaDanio().getDanio(TipoElemento::FUEGO, TipoElemento::AGUA) == 20.0f); // no tocada
    VERIFICAR(lector.getAdvertencias().empty());

    escribirArchivo(tmp + "/cfg_mal.txt",
        "cantidad_elementos 99\n"      // fuera de rango
        "ia GENIAL\n"                  // IA inexistente
        "danio AGUA PIEDRA 10\n"       // tipo inexistente
        "danio AGUA FUEGO abc\n"       // valor no numerico
        "cosa_rara 1\n"                // directiva desconocida
        "elementos_mixtos 1\n");       // esta si es valida
    Configuracion mal = lector.leer(tmp + "/cfg_mal.txt");
    VERIFICAR(lector.getAdvertencias().size() == 5);
    VERIFICAR(mal.getCantidadElementos() == 5);            // se mantuvo el valor por defecto
    VERIFICAR(mal.getElementosMixtos());                    // la linea valida si se aplico
}

static void compararPartidas(const PartidaGuardada& a, const PartidaGuardada& b)
{
    VERIFICAR(std::strcmp(a.nombreJugador, b.nombreJugador) == 0);
    VERIFICAR(a.idIA == b.idIA && a.turno == b.turno);
    VERIFICAR(a.cantidadJugador == b.cantidadJugador && a.cantidadIA == b.cantidadIA);
    VERIFICAR(a.activoJugador == b.activoJugador && a.activoIA == b.activoIA);
    for (int i = 0; i < a.cantidadJugador; ++i)
        VERIFICAR(a.jugador[i].id == b.jugador[i].id && a.jugador[i].energia == b.jugador[i].energia);
    for (int i = 0; i < a.cantidadIA; ++i)
        VERIFICAR(a.ia[i].id == b.ia[i].id && a.ia[i].energia == b.ia[i].energia);
}

static void pruebaPersistencia(const std::string& tmp)
{
    std::cout << "- Persistencia (clase -> struct -> archivo -> struct -> clase)\n";
    Configuracion cfg;
    cfg.setElementosMixtos(true);               // incluye mixtos para probar su reconstruccion
    GestorPartidas gestor(cfg, tmp + "/partidas");

    std::srand(7);
    std::unique_ptr<Partida> original(gestor.nuevaPartida("Beto", ID_IA_SUPERIA));
    for (int i = 0; i < 3; ++i) {
        original->setElementoActivoJugador(original->getJugador()->getElementosVivos().front());
        original->ejecutarRonda();
    }

    VERIFICAR(gestor.guardar(*original, "mi partida/../x"));     // nombre con caracteres raros
    auto lista = gestor.listarPartidas();
    VERIFICAR(lista.size() == 1);

    std::unique_ptr<Partida> cargada(gestor.cargar(lista.front()));
    VERIFICAR(cargada != nullptr);
    if (cargada) {
        compararPartidas(original->exportar(), cargada->exportar());
        VERIFICAR(cargada->getTurno() == 3);
        VERIFICAR(cargada->getIA()->getIdIA() == ID_IA_SUPERIA);
        // La partida cargada se puede seguir jugando.
        cargada->setElementoActivoJugador(cargada->getJugador()->getElementosVivos().front());
        VERIFICAR(!cargada->ejecutarRonda().empty());
    }

    // Archivos danados.
    RepositorioPartidas repo(tmp + "/partidas");
    PartidaGuardada basura{};
    VERIFICAR(!repo.cargar("no_existe", basura));
    escribirArchivo(tmp + "/partidas/corto.sav", "hola");
    VERIFICAR(!repo.cargar("corto", basura));
    PartidaGuardada malo = original->exportar();
    malo.magic = 123;
    VERIFICAR(repo.guardar("malo", malo));
    VERIFICAR(!repo.cargar("malo", basura));
    malo = original->exportar();
    malo.cantidadJugador = 99;
    VERIFICAR(repo.guardar("rango", malo));
    VERIFICAR(!repo.cargar("rango", basura));
    VERIFICAR(gestor.cargar("malo") == nullptr && !gestor.getUltimoError().empty());
    VERIFICAR(!repo.guardar("", malo));         // nombre vacio: se rechaza
}

static void pruebaPartidaCompleta()
{
    std::cout << "- Partidas completas contra cada IA\n";
    Configuracion cfg;
    for (int idIA : FabricaIA::ids()) {
        for (int semilla = 1; semilla <= 50; ++semilla) {
            std::srand(semilla);
            std::unique_ptr<Partida> p(FabricaPartida::crearNueva("Test", idIA, cfg));
            int rondas = 0;
            while (!p->hayGanador() && rondas < 500) {
                auto vivos = p->getJugador()->getElementosVivos();
                p->setElementoActivoJugador(vivos.front());
                p->ejecutarRonda();
                ++rondas;
            }
            VERIFICAR(p->hayGanador() && p->getGanador() != nullptr);
            VERIFICAR(p->getTurno() == rondas);
        }
    }
}

static void generarEjemplo(const std::string& carpeta)
{
    Configuracion cfg;
    GestorPartidas gestor(cfg, carpeta);
    std::srand(2026);
    std::unique_ptr<Partida> p(gestor.nuevaPartida("Jugador", ID_IA_SUPERIA));
    for (int i = 0; i < 3; ++i) {
        p->setElementoActivoJugador(p->getJugador()->getElementosVivos().front());
        p->ejecutarRonda();
    }
    if (gestor.guardar(*p, "ejemplo"))
        std::cout << "Partida de ejemplo escrita en " << carpeta << "/ejemplo.sav\n";
}

int main(int argc, char** argv)
{
    const std::string tmp = (fs::temp_directory_path() / "tppoo_pruebas").string();
    fs::remove_all(tmp);
    fs::create_directories(tmp + "/partidas");

    pruebaCombate();
    pruebaFabricas();
    pruebaConfiguracion(tmp);
    pruebaPersistencia(tmp);
    pruebaPartidaCompleta();

    if (argc == 3 && std::string(argv[1]) == "--ejemplo")
        generarEjemplo(argv[2]);

    std::cout << "\nResultado: " << (total - fallos) << "/" << total << " verificaciones OK\n";
    return fallos == 0 ? 0 : 1;
}
