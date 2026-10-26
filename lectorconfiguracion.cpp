#include "lectorconfiguracion.h"

#include <fstream>
#include <functional>
#include <map>
#include <sstream>
#include <stdexcept>

#include "estadoguardado.h"
#include "fabricaia.h"
#include "tipoelemento.h"

namespace {

using Directiva = std::function<void(std::istringstream&, Configuracion&)>;

// Cada directiva valida sus propios argumentos y lanza std::invalid_argument si no sirven.
const std::map<std::string, Directiva>& directivas()
{
    static const std::map<std::string, Directiva> tabla = {
        {"cantidad_elementos", [](std::istringstream& in, Configuracion& c) {
             int n = 0;
             if (!(in >> n) || n < 1 || n > MAX_ELEMENTOS)
                 throw std::invalid_argument("cantidad_elementos debe estar entre 1 y "
                                             + std::to_string(MAX_ELEMENTOS));
             c.setCantidadElementos(n);
         }},
        {"ia", [](std::istringstream& in, Configuracion& c) {
             std::string valor;
             if (!(in >> valor))
                 throw std::invalid_argument("falta el tipo de IA");
             c.setIdIA(FabricaIA::idDesdeClave(valor));
         }},
        {"elementos_mixtos", [](std::istringstream& in, Configuracion& c) {
             int valor = -1;
             if (!(in >> valor) || (valor != 0 && valor != 1))
                 throw std::invalid_argument("elementos_mixtos debe ser 0 o 1");
             c.setElementosMixtos(valor == 1);
         }},
        {"danio", [](std::istringstream& in, Configuracion& c) {
             std::string atacante, defensor;
             float valor = -1.0f;
             if (!(in >> atacante >> defensor >> valor) || valor < 0.0f || valor > 100.0f)
                 throw std::invalid_argument("uso: danio ATACANTE DEFENSOR PORCENTAJE(0-100)");
             c.configurarDanio(TiposElemento::desdeTexto(atacante),
                               TiposElemento::desdeTexto(defensor), valor);
         }}
    };
    return tabla;
}

std::string recortar(const std::string& texto)
{
    const char* espacios = " \t\r\n";
    size_t inicio = texto.find_first_not_of(espacios);
    if (inicio == std::string::npos) return "";
    size_t fin = texto.find_last_not_of(espacios);
    return texto.substr(inicio, fin - inicio + 1);
}

} // namespace

void LectorConfiguracion::advertir(const std::string& mensaje)
{
    advertencias.push_back(mensaje);
}

const std::vector<std::string>& LectorConfiguracion::getAdvertencias() const
{
    return advertencias;
}

void LectorConfiguracion::procesarLinea(const std::string& lineaCruda, int numeroLinea, Configuracion& config)
{
    const std::string linea = recortar(lineaCruda.substr(0, lineaCruda.find('#')));
    if (linea.empty()) return;

    std::istringstream entrada(linea);
    std::string clave;
    entrada >> clave;

    const std::string prefijo = "config.txt línea " + std::to_string(numeroLinea) + ": ";

    auto it = directivas().find(clave);
    if (it == directivas().end()) {
        advertir(prefijo + "directiva desconocida '" + clave + "' (ignorada)");
        return;
    }

    try {
        it->second(entrada, config);
    } catch (const std::exception& e) {
        advertir(prefijo + e.what() + " (línea ignorada)");
    }
}

Configuracion LectorConfiguracion::leer(const std::string& ruta)
{
    advertencias.clear();
    Configuracion config;

    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        advertir("No se encontró el archivo de configuración; se usan los valores por defecto.");
        return config;
    }

    std::string linea;
    int numero = 0;
    while (std::getline(archivo, linea))
        procesarLinea(linea, ++numero, config);

    return config;
}
