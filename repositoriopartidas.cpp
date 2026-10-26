#include "repositoriopartidas.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace {
const char* EXTENSION = ".sav";
}

RepositorioPartidas::RepositorioPartidas(const std::string& directorio)
    : directorio(directorio) {}

const std::string& RepositorioPartidas::getUltimoError() const { return ultimoError; }

// Deja solo letras, numeros, '_' y '-' (evita rutas raras como "../x").
std::string RepositorioPartidas::sanitizar(const std::string& nombre)
{
    std::string limpio = nombre;
    std::transform(limpio.begin(), limpio.end(), limpio.begin(), [](unsigned char c) {
        return (std::isalnum(c) || c == '_' || c == '-') ? static_cast<char>(c) : '_';
    });
    return limpio;
}

std::string RepositorioPartidas::rutaDe(const std::string& nombre) const
{
    return (fs::path(directorio) / (sanitizar(nombre) + EXTENSION)).string();
}

bool RepositorioPartidas::esValido(const PartidaGuardada& e, std::string& motivo)
{
    if (e.magic != MAGIC_PARTIDA)   { motivo = "no es un archivo de partida de este juego"; return false; }
    if (e.version != VERSION_PARTIDA) { motivo = "versión de archivo no compatible"; return false; }
    if (e.cantidadJugador < 1 || e.cantidadJugador > MAX_ELEMENTOS ||
        e.cantidadIA < 1 || e.cantidadIA > MAX_ELEMENTOS)
                                    { motivo = "cantidad de elementos fuera de rango"; return false; }
    if (e.activoJugador < -1 || e.activoJugador >= e.cantidadJugador ||
        e.activoIA < -1 || e.activoIA >= e.cantidadIA)
                                    { motivo = "índice de elemento activo inválido"; return false; }
    return true;
}

bool RepositorioPartidas::guardar(const std::string& nombre, const PartidaGuardada& estado) const
{
    if (sanitizar(nombre).empty()) {
        ultimoError = "El nombre de la partida está vacío.";
        return false;
    }

    std::error_code ec;
    fs::create_directories(directorio, ec);
    if (ec) {
        ultimoError = "No se pudo crear la carpeta de partidas: " + ec.message();
        return false;
    }

    std::ofstream salida(rutaDe(nombre), std::ios::binary | std::ios::trunc);
    if (!salida.is_open()) {
        ultimoError = "No se pudo abrir el archivo para escribir.";
        return false;
    }

    salida.write(reinterpret_cast<const char*>(&estado), sizeof(PartidaGuardada));
    salida.flush();
    if (!salida.good()) {
        ultimoError = "Error al escribir el archivo.";
        return false;
    }
    return true;
}

bool RepositorioPartidas::cargar(const std::string& nombre, PartidaGuardada& destino) const
{
    std::ifstream entrada(rutaDe(nombre), std::ios::binary);
    if (!entrada.is_open()) {
        ultimoError = "No se encontró la partida '" + nombre + "'.";
        return false;
    }

    PartidaGuardada leido{};
    entrada.read(reinterpret_cast<char*>(&leido), sizeof(PartidaGuardada));
    if (entrada.gcount() != static_cast<std::streamsize>(sizeof(PartidaGuardada))) {
        ultimoError = "El archivo está incompleto o dañado.";
        return false;
    }

    std::string motivo;
    if (!esValido(leido, motivo)) {
        ultimoError = "Archivo inválido: " + motivo + ".";
        return false;
    }

    leido.nombreJugador[MAX_NOMBRE - 1] = '\0';   // por si el archivo vino alterado
    destino = leido;
    return true;
}

std::vector<std::string> RepositorioPartidas::listar() const
{
    std::vector<std::string> nombres;

    std::error_code ec;
    fs::directory_iterator it(directorio, ec), fin;
    if (ec) return nombres;   // carpeta inexistente: no hay partidas

    for (; it != fin; it.increment(ec)) {
        if (ec) break;
        if (it->is_regular_file() && it->path().extension() == EXTENSION)
            nombres.push_back(it->path().stem().string());
    }
    std::sort(nombres.begin(), nombres.end());
    return nombres;
}
