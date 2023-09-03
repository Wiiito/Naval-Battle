#include "headers/players.hpp"

using namespace sf;
using namespace std;

Player::Player(Vector2i boardSizePx, Vector2i squaresCount, Texture *texture, int textureOffset, Sprite *gameScreenReference, int fs) {
    boardOffset = Vector2i(
        boardSizePx.x / squaresCount.x,
        boardSizePx.y / squaresCount.y);

    for (int i = 0; i < squaresCount.x; i++) {
        std::vector<int> vectorX;
        for (int j = 0; j < squaresCount.y; j++) {
            vectorX.push_back(0);
        }
        board.push_back(vectorX);
    }

    vector<int> boats = boatsQuantity;  // Clonando a boatsQuantity pra gerar os barcos

    while (!boats.empty()) {  // Usando a matriz pra gerar os barcos

        int lastIndice = boats.size() - 1;  // Pega o ultimo elemento do array do tamanho de barcos
        // Removendo ultimo elemento se ele chega a zero
        if (boats[lastIndice] <= 0) {
            boats.pop_back();
            boats.shrink_to_fit();
            continue;
        }

        int direction = rand() % 2;
        // Criando localizações a serem utilizadas, devem considerar a direção para a utilização da ultima casa
        int randX, randY;
        randX = rand() % (board.size() - boats.size() + !direction);
        randY = rand() % (board[0].size() - boats.size() + direction);

        /*
            Sequencia de um codigo genial (direction)
            E logo em seguida essa coisa feia ai de stop
        */
        // Checando se há elemento nas casas que o barco ocupara
        bool stop = false;
        for (int i = 0; i <= boats.size(); i++) {
            if (board[randX + i * direction][randY + i * !direction]) {
                stop = true;
                break;
            }
        }

        if (stop) {  // Deve ficar do lado de fora pois é preciso quebrar o loop de fora
            continue;
        }

        // Criando foguete e o agregando ao jogador
        Rocket *generateRocket = new Rocket(boats.size() + 1, direction, Vector2i(randX, randY));
        generateRocket->makeRocketBody(texture, textureOffset, gameScreenReference, boardOffset, fs);
        rockets.push_back(generateRocket);

        for (int i = 0; i <= boats.size(); i++) {  // Preenchendo o array com casas que não podem ser utilizadas
            int xAxis, yAxis;
            xAxis = randX + i * direction;
            yAxis = randY + i * !direction;

            // Marcando arredores
            board[std::max(0, xAxis - 1)][yAxis] = 1;                                             // Casa a esquerda
            board[std::min(squaresCount.x - 1, xAxis + 1)][yAxis] = 1;                                // Casa a direita
            board[xAxis][std::max(0, yAxis - 1)] = 1;                                             // Casa de cima
            board[xAxis][std::min(squaresCount.y - 1, yAxis + 1)] = 1;                                // Casa de baixo
            board[std::max(0, xAxis - 1)][std::max(0, yAxis - 1)] = 1;                            // Casa esquerda - cima
            board[std::min(squaresCount.x - 1, xAxis + 1)][std::max(0, yAxis - 1)] = 1;               // Casa direita - cima
            board[std::max(0, xAxis - 1)][std::min(squaresCount.y - 1, yAxis + 1)] = 1;               // Casa esquerda - baixo
            board[std::min(squaresCount.x - 1, xAxis + 1)][std::min(squaresCount.y - 1, yAxis + 1)] = 1;  // Casa direita - baixo
            board[xAxis][yAxis] = 1;                                                              // Casa atual
        }

        boats[lastIndice]--;
    }

    clearBoard();
}

void Player::clearBoard() {  // Limpa o tabuleiro
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j] = 0;
        }
    }
}

int Player::hit(Vector2i pos) {  // Marca uma casa atingida
    board[pos.x][pos.y] = 1;
    for (int i = 0; i < rockets.size(); i++) {
        if (rockets[i]->hit(pos)) {  // Entra se acertar (i é o foguete)

            if (rockets[i]->didDestroy()) {
                for (int j = 0; j < rockets.size(); j++) {
                    if (!rockets[j]->didDestroy()) {
                        return 2;  // Destruiu foguete
                    }
                }
                return 3;  // Usuario ganhou
            }

            return 1;  // Acertou um foguete
        }
    }
    // Retorna 0 se não acertar nada
    return 0;
}

void Player::printBoard(RenderWindow *pWindow) {
    for (int i = 0; i < rockets.size(); i++) {
        rockets[i]->draw(pWindow);
    }
}

Player::~Player() {
}
