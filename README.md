# Agua · Tierra · Fuego — TP Integrador POO (Tercera Entrega)

Juego por turnos tipo piedra-papel-tijera, en C++17 con Qt (widgets).

## Compilar y ejecutar
1. Abrir `TP2POOCartas.pro` en Qt Creator (Qt 5.15 o Qt 6) y ejecutar.
2. El programa busca `config.txt` junto al ejecutable, en la carpeta actual o en la carpeta
   del proyecto (ver `aplicacion/rutasaplicacion.cpp`). Las partidas se guardan en `partidas/`
   al lado de ese `config.txt`.

## Estructura (cada carpeta = una capa)
| Carpeta | Contenido | Depende de |
|---|---|---|
| `modelo/` | Reglas del juego: elementos, jugadores, IAs, tabla de daño, `Partida` | nada (ni Qt ni archivos) |
| `persistencia/` | `Configuracion`, `LectorConfiguracion`, `RepositorioPartidas`, structs de disco | `modelo/` |
| `aplicacion/` | `FabricaPartida`, `GestorPartidas`, `RutasAplicacion`: une todo para la interfaz | modelo, persistencia |
| `ui/` | Ventanas Qt: inicio, juego, fin de partida, carta de elemento | aplicacion, modelo |
| `pruebas/` | Pruebas de consola (sin Qt) de reglas, configuración y persistencia | — |

## config.txt
Una directiva por línea; `#` inicia un comentario.
```
cantidad_elementos 5          # 1 a 16
ia SUPERIA                    # ALEATORIA | ESTRATEGICA | SUPERIA
elementos_mixtos 0            # 1 = reparte también Barro, Lava y Vapor
danio AGUA FUEGO 50           # danio ATACANTE DEFENSOR PORCENTAJE
```
Si el archivo no existe se usan valores por defecto; las líneas inválidas se ignoran y la
pantalla de inicio muestra un aviso con cada una.

## Partidas guardadas
`partidas/<nombre>.sav`: un bloque binario con el struct `PartidaGuardada`
(ver `persistencia/estadoguardado.h`). `partidas/ejemplo.sav` es un ejemplo (3 rondas jugadas).

## Pruebas
```
cd pruebas && qmake pruebas.pro && make && ./pruebas
```
