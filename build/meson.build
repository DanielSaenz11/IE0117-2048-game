project(2048, c,
  version: 1.0,
  default_options: [warning_level=3, c_std=c11])

#Dependencia de SDL2
sdl2 = dependency(sdl2)

#Directorios de inclusion
inc = include_directories(include)

#Archivos fuente
game_sources = files(src/game-logic.c, src/movement.c)
gui_sources = files(src/gui.c)
main_source = files(src/main.c)

#Se unen todos los archivos fuente en una sola linea 
src = game_sources + gui_sources + main_source

#Se genera el ejecutable '2048'
executable(2048, src,
  include_directories: inc,
  dependencies: sdl2)
