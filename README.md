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
<br />
<div align="center">
  <a href="https://github.com/DanielSaenz11/IE0117-2048-game">
    <img src="https://github.com/DanielSaenz11/IE0117-2048-game/blob/main/2048.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Proyecto final Programación bajo plataformas abiertas - 2048</h3>

  <p align="center">
    Crear un programa interactivo del juego 2048 en lenguaje de progrmación C.
    <br />
    
</div>

## Colaboradores
- **Daniel Alberto Sáenz Obando** - C37099
- **Elsa Valeria Roman Astua** - C26910
- **Rodrigo Madrigal Montes** - C24458
<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- TABLA DE CONTENIDOS -->
<details>
  <summary>Tabla de contenidos</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## Acerca del proyecto

### Objetivo general

**Crear un programa interactivo del juego 2048 en el lenguaje de programación C, por medio del uso de la biblioteca open source SDL2 para la interfaz gráfica del proyecto.**

### Objetivos específicos

1. **Lógica de programación del juego 2048**
    - Condiciones de victoria/derrota
    - Movimientos
    - Combinación de casillas
2. **Interfaz gráfica con la biblioteca SDL2**
3. **Documentación detallada del proyecto en GitHub**
    - Instalación de bibliotecas
    - Compilación
    - Ejecución

## Alcances

1. **Interfaz gráfica simple**
    - Animaciones sencillas de unión de casillas
    - Puntuación y puntuación máxima arriba del tablero
    - Tiempo jugado
2. **Plataforma: Linux**
3. **Tablero**
    - 3-5 casillas por lado
4. **Input del usuario**
    - Flechas del teclado

## Bibliotecas requeridas

### SDL2
La siguiente imagen es con fines ilustrativos de la forma en que se va observar el juego al terminar su implementación.

  <a href="https://github.com/DanielSaenz11/IE0117-2048-game">
    <img src="https://github.com/DanielSaenz11/IE0117-2048-game/blob/main/2048.png" alt="Logo" width="80" height="80">
  </a>

### Otras bibliotecas

1. `time.h`
    - Tiempo transcurrido y posición de nuevas casillas
2. `stdio.h`
3. `stdlib.h`
    - Memoria dinámica para el manejo del arreglo de números variable


## Instalación de las bibliotecas SDL2 y SDL2_ttf

### SDL2

Primero se deben actualizar los paquetes del sistema ejecutando el siguiente comando y siguiendo las instruccciones

 ```sh
   sudo apt-get update 
```

Ahora se ejecuta el siguiente comando para instalar la biblioteca `SDL2`

 ```sh
   sudo apt-get install libsdl2-dev
```

Con esto ya debería haberse instalado la biblioteca `SDL2`. Para corroborar la Instalación  podemos utilizar el siguiente comando:

```sh
   ls /usr/include/SDL2/SDL.h
```
Este es el archivo de encabezado de la biblioteca, si existe en el sistema se muestra que la biblioteca fue instalada correctamente. 

### SDL2_ttf

Igual que con la biblioteca anterior se ejecuta este comando para instalar `SDL2_ttf`

 ```sh
   sudo apt-get install libsdl2-ttf-dev
```

Y con esto ya tendríamos las dependencias necesarias instaladas

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Ejecución del build system (Meson)

Primero se debe instalar Meson en el equipo con el siguiente comando

 ```sh
   pip install meson
```

Además se debe instalar Ninja, que es el sistema de construcción utilizado por defecto en Meson, con este comando

 ```sh
   sudo apt-get install ninja-build
```

Con esto ya tenemos instalado lo necesario. Como siguiente paso clona el repositorio de este proyecto y dirigirse al directorio del mismo

```sh
   git clone https://github.com/DanielSaenz11/IE0117-2048-game.git
   cd IE0117-2048-game
```

Posteriormente ir al directorio `build` y compilar el proyecto utilizando el comando `ninja` 

```sh
   cd build
   ninja
```

Y por último ejecutar el ejecutable generado

```sh
   ./2048
```




<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Feature 1
- [ ] Feature 2
- [ ] Feature 3
    - [ ] Nested Feature

See the [open issues](https://github.com/github_username/repo_name/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Your Name - [@twitter_handle](https://twitter.com/twitter_handle) - email@email_client.com

Project Link: [https://github.com/github_username/repo_name](https://github.com/github_username/repo_name)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* []()
* []()
* []()

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
# IE0117-2048-game
Repositorio para el proyecto final del curso IE-0117 Programación bajo plataformas abiertas de Ingeniería Eléctrica en la Universidad de Costa Rica.
