# Naval Battle in C++/SFML

Um jogo de Batalha Naval feito em c++ com o uso da biblioteca SFML.
Este foi um jogo feito como atividade no CEFET-MG/Contagem.

## Instalação

Para compilar, foi utilizado make.
Portanto, altere a localização da instalação do sfml.
No caso apresentado, os arquivos se encontravam dentro da pasta do projeto.

![Organização SFML](https://i.imgur.com/VRgmqvG.png)

```bash
  all: compile link

compile:
	g++ -ISFML/include -c main.cpp

link:
	g++ main.o -o main -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
```

## Compilando

Para compilar rode

```bash
  make
```

## Autores

- [@ellismorenna](https://www.github.com/ellismorenna)
- [@ErickRezende](https://www.github.com/ErickRezende)
- [@Wiiito](https://www.github.com/wiiito)

## Tecnologias:

**Render:** SFML

**Back-end:** Pure c++

**Compilação**: make

## Dependências

 - [TinyXML2](https://github.com/terroo/tinyxml2/)