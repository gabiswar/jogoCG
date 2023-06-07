#include "jogo.h"
#include <iostream>

void teclaPressionada(unsigned char key, int x, int y) {
    switch (key) {
        case 80: //P

            printf("entrei no P");
            break;
        case 68: //p
            printf("entrei no d");
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void teclaSolta(unsigned char key, int x, int y) {
    switch (key) {
        case 80: //P

            printf("SAI no P");
            break;
        case 68: //p
            printf("SAI no d");
            break;
        default:
            break;
    }
    glutPostRedisplay();
}



void renderSceneJogando() {

}
