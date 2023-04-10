#include "header.hpp"

Player::Player() {
    windowOffset = Vector2i(
        boardSize.x / sizeBoardX,
        boardSize.y / sizeBoardY
    );

    for (int i = 0; i < sizeBoardX; i++) {
        std::vector<int> vectorX;
        for (int j = 0; j < sizeBoardY; j++) {
            vectorX.push_back(0);
        }
        board.push_back(vectorX);
    }

    std::vector<int> boats = boatsQuantity;  // Clonando a boatsQuantity pra gerar os barcos

    while (!boats.empty()) {  // Usando a matriz pra gerar os barcos
        int direction = rand() % 2;
        // Criando localizações a serem utilizadas, devem considerar a direção para a utilização da ultima casa
        int randX, randY;
        randX = rand() % (board.size() - boats.size() + !direction);
        randY = rand() % (board[0].size() - boats.size() + direction);


        int lastIndice = boats.size() - 1;  // Pega o ultimo elemento do array do tamanho de barcos

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
        rockets.push_back(generateRocket);

        for (int i = 0; i <= boats.size(); i++) {  // Preenchendo o array com casas que não podem ser utilizadas
            int xAxis, yAxis;
            xAxis = randX + i * direction;
            yAxis = randY + i * !direction;

            // Marcando arredores
            board[std::max(0, xAxis - 1)][yAxis] = 1;                                             // Casa a esquerda
            board[std::min(sizeBoardX - 1, xAxis + 1)][yAxis] = 1;                                // Casa a direita
            board[xAxis][std::max(0, yAxis - 1)] = 1;                                             // Casa de cima
            board[xAxis][std::min(sizeBoardY - 1, yAxis + 1)] = 1;                                // Casa de baixo
            board[std::max(0, xAxis - 1)][std::max(0, yAxis - 1)] = 1;                            // Casa esquerda - cima
            board[std::min(sizeBoardX - 1, xAxis + 1)][std::max(0, yAxis - 1)] = 1;               // Casa direita - cima
            board[std::max(0, xAxis - 1)][std::min(sizeBoardY - 1, yAxis + 1)] = 1;               // Casa esquerda - baixo
            board[std::min(sizeBoardX - 1, xAxis + 1)][std::min(sizeBoardY - 1, yAxis + 1)] = 1;  // Casa direita - baixo
            board[xAxis][yAxis] = 1;                                                              // Casa atual
        }

        // Removendo ultimo elemento se ele chega a zero
        boats[lastIndice]--;
        if (boats[lastIndice] == 0) {
            boats.pop_back();
            boats.shrink_to_fit();
        }
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

bool Player::hit(Vector2i pos) {  // Marca uma casa atingida
    for (int i = 0; i < rockets.size(); i++) {
        if (rockets[i]->hit(pos)) {
            board[pos.x][pos.y] = 1;
            return true;
        }
    }
    return false;
}

void Player::printBoard() {
    for (int i = 0; i < rockets.size(); i++) {
        rockets[i]->draw();
    }
}

Player::~Player() {
}
