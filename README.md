<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links



<!-- PROJECT LOGO -->

# IE0117-2048-game

<br />
<div align="center">
  <a href="https://github.com/DanielSaenz11/IE0117-2048-game">
    <img src="https://github.com/DanielSaenz11/IE0117-2048-game/blob/main/2048.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Proyecto final Programación bajo plataformas abiertas - 2048</h3>

  <p align="center">
    Crear un programa interactivo del juego 2048 en lenguaje de programación C.
    <br />
    
</div>

A modo de descripción general, este repositorio consiste en la implementación con el lenguaje de programación de C del juego 2048. Este juego consiste en un tablero, donde los jugadores deslizan fichas numeradas con múltiplos de 2 en una cuadrícula para combinarlas y crear una ficha con el valor de 2048.

## Colaboradores
- **Daniel Alberto Sáenz Obando** - C37099
- **Elsa Valeria Roman Astua** - C26910
- **Rodrigo Madrigal Montes** - C24458

## Instalación de las bibliotecas SDL2 y SDL2_ttf

### SDL2

Primero se deben actualizar los paquetes del sistema ejecutando el siguiente comando y siguiendo las instruccciones:

 ```sh
   sudo apt-get update 
```

Ahora, se ejecuta el siguiente comando para instalar la biblioteca `SDL2`:

 ```sh
   sudo apt-get install libsdl2-dev
```

Con esto ya debería haberse instalado la biblioteca `SDL2`. Para corroborar la instalación, se utiliza el siguiente comando:

```sh
   pkg-config --list-all | grep sdl2
```
Si existe en el sistema, se muestra que la biblioteca fue instalada correctamente. 

### SDL2_ttf

Igual que con la biblioteca anterior se ejecuta este comando para instalar `SDL2_ttf`:

 ```sh
   sudo apt-get install libsdl2-ttf-dev
```
Para comprobar su existencia en el sistema:

```sh
   pkg-config --list-all | grep SDL2_ttf
```

### Instalacion de fuente tipografica
Para el texto que aparece en la ventana grafica fue necesario instalar una fuente tipografica. 
1. Acceder a FontSpace desde el navegador al siguiente link:
  ```
  https://www.fontspace.com/night-pumpkind-font-f86994
  ```
4. Descargar la fuente y colocar el destino de descarga el directorio del presente repositorio.
6. Descomprimir el archivo zip de descarga puede ser manualmente en bibliotecas o ejecutando el siguiente comando:
   ```sh
      unzip nigth-pumpkind-font.zip
   ```
7. Extraer el archivo con la fuente que tiene extension .ttf
8. Otorgarle los permisos de ejecución de la fuente de la siguiente manera:
   ```sh
      chmod +w “NightPumpkind-1GpGv.ttf"

## Ejecución del build system (Meson)

Primero se debe instalar Meson en el equipo con el siguiente comando:

 ```sh
   pip3 install --user meson 
```

Esto instala meson en el path `~/.local/`, por lo cual hay que agregarl `~/.local/bin` al PATH:

 ```sh
   export PATH=$PATH:~/.local/bin
```

Además se debe instalar Ninja, que es el sistema de construcción utilizado por defecto en Meson, con este comando:

 ```sh
   sudo apt-get install ninja-build
```

Como siguiente paso, se clona el repositorio de este proyecto y se dirige hacia el directorio del mismo:

```sh
   git clone https://github.com/DanielSaenz11/IE0117-2048-game.git
   cd IE0117-2048-game
```

Posteriormente, se escribe el siguiente comando para ejecutar configurar el meson en una carpeta que se llamará `build`:
```sh
   meson setup build
```

Ahora, debe compilar con el comando `ninja`:

```sh
   ninja -C build
```

Por último, ejecutar el ejecutable generado `2048`:

```sh
   ./build/2048
```

## Instrucciones de juego
Después de la compilación, se tiene que el juego funciona de manera que, los movimientos de las casillas se realizan con las flechas del teclado. En caso de querer salir del juego, se puede cerrar la ventana, tocar la tecla ESCAPE o la tecla `q`. Ahora bien, durante el juego, con cada movimiento aparecen nuevas casillas en posiciones aleatorias. Si dos casillas son iguales y no hay ninguna casilla ocupada entre ellas, entonces si se mueve una de ellas hacia la otra, las casillas se fusionan y pasan a tener el doble del valor anterior.

Por un lado, la condición de pérdida del juego consiste en que el tablero se llene y que no haya un movimiento disponible válido. En ese caso, se cierra la ventana y se muestra un mensaje que indica el resultado en la terminal.

Por otro lado, la condición de victoria corresponde a que se fusionen las casillas y se llegue a un caso donde se forma una casilla con valor 2048. En ese momento, se cierra la ventana y se muestra un mensaje de victoria.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
