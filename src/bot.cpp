#include "header.hpp"

Bot::Bot() {
    randPos.x = 0;
    randPos.y = 0;

    nextHit.x = 0;
    nextHit.y = 0;

    destroying = false;

    //difficulty = 1;

    getRandPos();
}

void Bot::getRandPos() {
    randPos.x = rand() % sizeBoardX;
    randPos.y = rand() % sizeBoardY;
}

void Bot::hitPos() {
    switch (Players[!currentPlayer].hit(Vector2i(randPos.x + nextHit.x, randPos.y + nextHit.y))){
        case 0: // Nao acertou
            if (destroying){
                //
            }else {
                getRandPos();
            }
            break;

        case 1: // Acertou  
            if (nextHit == Vector2f(0, 0)){
                destroying = true;
            } else {
                destroying = false;

                randPos.x = randPos.x + nextHit.x;
                randPos.y = randPos.y + nextHit.y;

            }

            break;

        case 2: // Destruiu
            destroying = false;
            getRandPos();
            nextHit.x = 0;
            nextHit.y = 0;

            break;

        default:
            break;

    }

    if (destroying) {
        do{
            if (nextHit.y == 1){
                nextHit.y = -1;
            } else if(nextHit.y == -1){
                nextHit.x = -1;
                nextHit.y = 0;
            } else if (nextHit.x == -1){
                nextHit.x = 1;
                nextHit.y = 0;
            } else if (nextHit == Vector2f(0, 0)){ 
                nextHit.y++;
            }
        } while(randPos.x + nextHit.x < 0 || randPos.x + nextHit.x > sizeBoardX || randPos.y + nextHit.y < 0 || randPos.y + nextHit.y > sizeBoardY);
        
    } else {
        getRandPos();
    }
    
}
