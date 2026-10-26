#include "rutasaplicacion.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

std::string RutasAplicacion::directorioBase(const std::string& directorioEjecutable)
{
    std::vector<fs::path> candidatos;
    std::error_code ec;

    candidatos.push_back(fs::current_path(ec));
    fs::path actual = directorioEjecutable;
    for (int nivel = 0; nivel < 4; ++nivel) {
        candidatos.push_back(actual);
        actual = actual.parent_path();
    }
#ifdef RUTA_PROYECTO
    candidatos.push_back(fs::path(RUTA_PROYECTO));
#endif

    for (const fs::path& carpeta : candidatos) {
        if (fs::exists(carpeta / "config.txt", ec))
            return carpeta.string();
    }

#ifdef RUTA_PROYECTO
    return RUTA_PROYECTO;
#else
    return fs::current_path(ec).string();
#endif
}
