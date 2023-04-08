#include "header.hpp"

Player::Player() {
    for (int i = 0; i < sizeBoardX; i++) {
        std::vector<int> vectorX;
        for (int j = 0; j < sizeBoardY; j++) {
            vectorX.push_back(0);
        }
        board.push_back(vectorX);
    }

    std::vector<int> boats = boatsQuantity;  // Clonando a boatsQuantity pra gerar os barcos

    while (!boats.empty()) {
        int randX, randY;
        randX = rand() % (board.size() - boats.size());
        randY = rand() % (board[0].size() - boats.size());

        int direction = rand() % 2;
        int lastIndice = boats.size() - 1;

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

        for (int i = 0; i <= boats.size(); i++) {
            int xAxis, yAxis;
            xAxis = randX + i * direction;
            yAxis = randY + i * !direction;

            board[std::max(0, xAxis - 1)][yAxis] = boats.size() + 1;                                             // Casa a esquerda
            board[std::min(sizeBoardX - 1, xAxis + 1)][yAxis] = boats.size() + 1;                                // Casa a direita
            board[xAxis][std::max(0, yAxis - 1)] = boats.size() + 1;                                             // Casa de cima
            board[xAxis][std::min(sizeBoardY - 1, yAxis + 1)] = boats.size() + 1;                                // Casa de baixo
            board[std::max(0, xAxis - 1)][std::max(0, yAxis - 1)] = boats.size() + 1;                            // Casa esquerda - cima
            board[std::min(sizeBoardX - 1, xAxis + 1)][std::max(0, yAxis - 1)] = boats.size() + 1;               // Casa direita - cima
            board[std::max(0, xAxis - 1)][std::min(sizeBoardY - 1, yAxis + 1)] = boats.size() + 1;               // Casa esquerda - baixo
            board[std::min(sizeBoardX - 1, xAxis + 1)][std::min(sizeBoardY - 1, yAxis + 1)] = boats.size() + 1;  // Casa direita - baixo
            board[xAxis][yAxis] = boats.size() + 1;                                                              // Casa atual
        }

        // Removendo ultimo elemento se ele chega a zero
        boats[lastIndice]--;
        if (boats[lastIndice] == 0) {
            boats.pop_back();
            boats.shrink_to_fit();
        }
    }

    printBoard();
}

void Player::printBoard() {
    for (int i = 0; i < board[0].size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            std::cout << board[j][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Player::~Player() {
}
