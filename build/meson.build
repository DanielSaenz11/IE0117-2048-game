project('2048', 'c',
  version: '1.0',
  default_options: ['warning_level=3', 'c_std=c11'])

# Dependencias SDL2 y SDL2_ttf
sdl2 = dependency('sdl2')
sdl2_ttf = dependency('SDL2_ttf')

# Directorios de inclusión
inc = include_directories('include')

# Archivos fuente
game_sources = files('src/game-logic.c', 'src/movement.c')
gui_sources = files('src/gui.c')
main_source = files('src/main.c')

# Se unen todos los archivos fuente en una sola línea 
src = game_sources + gui_sources + main_source

# Se genera un solo ejecutable '2048'
executable('2048', src,
  include_directories: inc,
  dependencies: [sdl2, sdl2_ttf])

