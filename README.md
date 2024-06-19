
<div id="header" align="center">

# Cifrado y descifrado seguro de archivos


</div>
#
Este proyecto tiene como objetivo desarrollar un sistema robusto para cifrar y descifrar archivos .txt utilizando C++, H++ y CMake.

El objetivo principal de este proyecto fue mejorar la seguridad de archivos .txt confidenciales mediante la implementación de técnicas de cifrado avanzadas. 

C++ se empleó por su eficiencia, velocidad y versatilidad, lo que lo convierte en una opción ideal para manejar operaciones de archivos complejas y realizar el procesamiento necesario para el cifrado y descifrado de datos. H++, conocido por sus sólidas capacidades de cifrado, se integró en el proyecto para proporcionar capas de seguridad adicionales. Esto permitió utilizar bibliotecas de cifrado avanzadas, garantizando que los datos confidenciales estuvieran adecuadamente protegidos contra accesos no autorizados.

CMake se utilizó como el sistema de compilación, facilitando la configuración del proyecto en diferentes plataformas y asegurando una integración perfecta de varios componentes del proyecto. Este sistema de construcción eficiente permitió gestionar el proceso de compilación de manera efectiva, asegurando que todos los elementos del proyecto se integraran sin problemas y que el entorno de desarrollo fuera coherente y manejable.

En resumen, este proyecto combinó el poder de C++, H++ y CMake para crear una solución fiable y segura destinada a proteger archivos .txt críticos mediante técnicas de cifrado avanzadas, garantizando al mismo tiempo la eficiencia y facilidad de uso en diferentes plataformas.

<div id="header" align="center">

<table>
  <tr>
    <td align="center">
      <a href="https://en.cppreference.com/w/">
        <img src="https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
      </a>
    </td>
    <td align="center">
      <a href="https://en.cppreference.com/w/">
        <img src="https://img.shields.io/badge/C-99-blue?style=for-the-badge&logo=c&logoColor=white" alt="C">
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/hush-shell/hush">
        <img src="https://img.shields.io/badge/H++-1.0.0-green?style=for-the-badge&logo=h%2B%2B&logoColor=white" alt="H++ (Hush Language)">
      </a>
    </td>
    <td align="center">
      <a href="https://cmake.org/">
        <img src="https://img.shields.io/badge/CMake-3.18.2-blue?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake">
      </a>
    </td>
    <td align="center">
      <a href="https://git-scm.com/">
        <img src="https://img.shields.io/badge/Git-2.31.1-orange?style=for-the-badge&logo=git&logoColor=white" alt="Git">
      </a>
    </td>
 
  
   <td align="center">
      <a href="https://www.mysql.com/">
        <img src="https://img.shields.io/badge/MySQL-8.0.23-blue?style=for-the-badge&logo=mysql&logoColor=white" alt="MySQL">
      </a>
    </td>
  
  <td align="center">
      <a href="https://invisible-island.net/ncurses/">
        <img src="https://img.shields.io/badge/Ncurses-6.2-blue?style=for-the-badge&logo=terminal&logoColor=white" alt="Ncurses">
      </a>
    </td>
  
 </tr>

</table>

</div>

## Captura de pantalla 

<div id="header" align="center">
  

 ![Screenshot from 2024-06-18 20-44-25](https://github.com/guillermo-gordon18-2000/EncryptorProyect/assets/83618044/5f9f470c-246a-4df5-840f-80ae55b13ae0) 
</div>
  
## Autor

- [@guillermo-gordon18-2000](https://www.github.com/guillermo-gordon18-2000)


## Caracteristicas 
#### Componentes clave

- C++: se utilizó C++ para la lógica de programación central de los algoritmos de cifrado y descifrado. Su eficiencia, velocidad y versatilidad lo convirtieron en una opción ideal para manejar operaciones de archivos complejas.

-  H++ (Hush Language): H++ se integró en el proyecto para proporcionar capas de seguridad adicionales a través de sus bibliotecas de cifrado. H++ es conocido por sus sólidas capacidades de cifrado, lo que lo hace adecuado para proteger datos confidenciales.

- CMake: CMake se empleó como sistema de compilación para gestionar el proceso de compilación de manera eficiente. Facilitó la configuración del proyecto en diferentes plataformas, asegurando una integración perfecta de varios componentes.

- Registro de MySQL: el proyecto incorporó una base de datos MySQL para fines de registro, registrando información detallada sobre cada operación de cifrado y descifrado realizada en los archivos .txt. Este mecanismo de registro mejoró la trazabilidad y la responsabilidad en las actividades de gestión de archivos.

- Ncurses: Ncurses es una biblioteca de software libre que proporciona funciones para crear interfaces de usuario basadas en texto en terminales de sistemas Unix-like. 

## Objetivos del proyecto:

- Desarrolle un sistema seguro de cifrado y descifrado de archivos utilizando algoritmos avanzados.
Implemente medidas de seguridad sólidas para proteger los archivos .txt confidenciales del acceso no autorizado.
Utilice el registro de MySQL para mantener un registro completo de todas las operaciones de archivos con fines de auditoría.
Al combinar el poder de C++, H++ y CMake, junto con las capacidades de registro de MySQL, este proyecto tuvo como objetivo proporcionar una solución confiable para proteger archivos .txt críticos mediante cifrado y al mismo tiempo garantizar la transparencia a través de mecanismos de registro detallados.
## Requisitos del Proyecto

### Tecnologías Utilizadas

<table>
  <tr>
    <td align="center">
      <a href="https://isocpp.org/">
        <img src="https://img.shields.io/badge/C++-11/14/17-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/hush-shell/hush">
        <img src="https://img.shields.io/badge/H++-1.0.0-green?style=for-the-badge&logo=h%2B%2B&logoColor=white" alt="H++ (Hush Language)">
      </a>
    </td>
    <td align="center">
      <a href="https://cmake.org/">
        <img src="https://img.shields.io/badge/CMake-3.20-blue?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake">
      </a>
    </td>
    <td align="center">
      <a href="https://www.mysql.com/">
        <img src="https://img.shields.io/badge/MySQL-8.0-orange?style=for-the-badge&logo=mysql&logoColor=white" alt="MySQL">
      </a>
    </td>
    <td align="center">
      <a href="https://git-scm.com/">
        <img src="https://img.shields.io/badge/Git-2.32.0-red?style=for-the-badge&logo=git&logoColor=white" alt="Git">
      </a>
    </td>

   <td align="center">
  <a href="https://invisible-island.net/ncurses/">
    <img src="https://img.shields.io/badge/Ncurses-6.2-blue?style=for-the-badge&logo=terminal&logoColor=white" alt="Ncurses">
  </a>
</td>
  </tr>
</table>

### Librerías y Dependencias Necesarias

- ![libmysqlcppconn-dev](https://img.shields.io/badge/libmysqlcppconn--dev-8.0-orange?style=for-the-badge&logo=mysql&logoColor=white) Conector MySQL para C++.
- ![libboost-all-dev](https://img.shields.io/badge/libboost--all--dev-1.75.0-blue?style=for-the-badge&logo=boost&logoColor=white) Conjunto de bibliotecas C++ para tareas como procesamiento de señales, sistemas de archivos, y más.

### Herramientas Necesarias

- ![CMake](https://img.shields.io/badge/CMake-3.20-blue?style=for-the-badge&logo=cmake&logoColor=white) Sistema de construcción y administración de proyectos multiplataforma.
- ![Git](https://img.shields.io/badge/Git-2.32.0-red?style=for-the-badge&logo=git&logoColor=white) Sistema de control de versiones distribuido para seguimiento de cambios en el código fuente.
- ![MySQL](https://img.shields.io/badge/MySQL-8.0-orange?style=for-the-badge&logo=mysql&logoColor=white) Sistema de gestión de bases de datos relacional para almacenamiento y recuperación de datos.
## Ejecutar Local

### Clonar el proyecto desde GitHub:
      ```bash
      git clone https://github.com/guillermo-gordon18-2000/EncryptorProyect.git

     ```bash

### Navegar a la carpeta del proyecto: 


cd EncryptorProyect
  


### Configurar el proyecto

#### CMake:

### 1. Asegúrate de tener CMake instalado en tu sistema.
### 2. Crea un directorio para la compilación y navega a él:
mkdir build
cd build

### 3. Ejecuta CMake para configurar el proyecto:
cmake ..

### 4. Compila el proyecto:
make

### Configurar la base de datos MySQL:

### 1. Asegúrate de que MySQL Server esté instalado y en ejecución.
### 2. Crea una base de datos para el proyecto en MySQL si aún no existe:
mysql -u tu_usuario -p -e "CREATE DATABASE encryptor_db;"


# Ejecutar la aplicación

##### 1. Asegúrate de estar en el directorio de compilación:
cd EncryptorProyect

##### 2. Ejecuta la aplicación:
./encrypor
