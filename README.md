
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
    
## Diretorio

- SFML
- - include
- - bin

- main.cpp

- dll's


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




## Screenshots

#### Tela inicial

![Start Screen](https://i.imgur.com/s3juhUv.png)


#### Seleção Linguas

![LangSelect](https://i.imgur.com/yFBEnYx.png)

#### Configurações

![Config](https://i.imgur.com/8PuGhbf.png)

#### Configurações

![Game mode](https://i.imgur.com/CDFL5LM.png)

#### Jogo

![Game](https://i.imgur.com/HtoQ0nZ.png)

## Funcionalidades
##### Extras

- Seleção de modo de jogo
- Singleplayer e Multiplayer
- 100% Responsivo para todas as resoluções em tela cheia
- Sistema de tradução via XML
- Animação ao atirar dinamica
- Tabuleiro dinamico
- Quantidade dinamica de barcos
- Quantidade dinamica de bombas
- Tamanho dinamico para o Tabuleiro
- "Biblioteca" criada para o projeto, reconhece clique, cria textos com fontes definidas previamente. Há também a criação da função que muda o valor das variaveis conforme clique desenhada na frente do texto passado como parâmentro.

##### Base
- Geração dos barcos sem encostar
- Posicionamento dos barcos aleatoriamente
- Reinicio do jogo sem fecha-lo
- Utilização da Biblioteca grafica SFML para sons e imagens
