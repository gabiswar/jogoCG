#include "jogo.h"
#include <iostream>
#include <math.h>

int windowW = 800;
int windowH = 600;

//--------------Inimigo Cena 1
float squareSize = 50.0f;
float squarePosX = (windowW - squareSize) / 2;
float squarePosY = (windowH - squareSize) / 2;

//--------------Tiros
float bulletRadius = 10.0f;
float bulletPosX[4]; // Array para armazenar as posi��es x dos tiros
float bulletPosY[4]; // Array para armazenar as posi��es y dos tiros
float bulletSpeed = 2.0f;
float bulletAngle[4]; // Array para armazenar os �ngulos dos tiros

//----------Personagem
float X = 450;
float Y = 20;
float comp = 103.2;
float alt = 177.9;

bool pause = false;
bool esq = false;
bool dir = false;
bool cima = false;
bool baixo = false;

void drawInimigoLevel1() {
    glBegin(GL_QUADS);
    glVertex2f(squarePosX, squarePosY);
    glVertex2f(squarePosX + squareSize, squarePosY);
    glVertex2f(squarePosX + squareSize, squarePosY + squareSize);
    glVertex2f(squarePosX, squarePosY + squareSize);
    glEnd();
}

void drawTiro(int index) {
    glPushMatrix();
    glTranslatef(bulletPosX[index], bulletPosY[index], 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        float x = bulletRadius * cos(angle);
        float y = bulletRadius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

void initTiros() {
    // Inicializa as posi��es dos tiros
    float diagonalOffset = squareSize * sqrt(2) / 2; // Dist�ncia entre o centro do quadrado e as diagonais
    bulletPosX[0] = squarePosX + squareSize / 2 + diagonalOffset;
    bulletPosY[0] = squarePosY + squareSize / 2 + diagonalOffset;
    bulletPosX[1] = squarePosX + squareSize / 2 - diagonalOffset;
    bulletPosY[1] = squarePosY + squareSize / 2 + diagonalOffset;
    bulletPosX[2] = squarePosX + squareSize / 2 + diagonalOffset;
    bulletPosY[2] = squarePosY + squareSize / 2 - diagonalOffset;
    bulletPosX[3] = squarePosX + squareSize / 2 - diagonalOffset;
    bulletPosY[3] = squarePosY + squareSize / 2 - diagonalOffset;

    // Inicializa os �ngulos dos tiros
    bulletAngle[0] = 0.0f;
    bulletAngle[1] = 0.5f * M_PI;
    bulletAngle[2] = M_PI;
    bulletAngle[3] = 1.5f * M_PI;
}

void updateTiro(int index) {
    bulletPosX[index] += bulletSpeed * cos(bulletAngle[index]);
    bulletPosY[index] += bulletSpeed * sin(bulletAngle[index]);

    // Verifica se o tiro chegou ao final da tela
    if (bulletPosX[index] < 0 || bulletPosX[index] > windowW || bulletPosY[index] < 0 || bulletPosY[index] > windowH) {
        // Reposiciona o tiro no centro da tela
        bulletPosX[index] = windowW / 2;
        bulletPosY[index] = windowH / 2;
    }

    // Verifica a colisão entre o tiro e o personagem
    if (bulletPosX[index] >= X && bulletPosX[index] <= X + comp && bulletPosY[index] >= Y && bulletPosY[index] <= Y + alt) {
        // O tiro colidiu com o personagem
        printf("COLIDIU");
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Muda a cor do fundo para verde
    }
}

void teclaPressionada(unsigned char key, int x, int y) {
    switch (key) {
    case 80: //P
    case 112: //p
        printf("P\n");
        break;
    case 87: //w
    case 119: //W
    	if (cima == false) {
		cima = true;
		baixo = false;
    	}
        break;
    case 83: //s
    case 115: //S
    	if (baixo == false) {
		cima = false;
		baixo = true;
    	}
        break;
    case 65: //a
    case 97: //A
    	if (esq == false) {
		esq = true;
		dir = false;
    	}
        break;
    case 68: //d
    case 100: //D
    	if(dir == false) {
		esq = false;
		dir = true;;
    	}
        break;
    case 27:      // Tecla "ESC"
        exit(0);  // Sai da aplicação
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

void renderCenaFase1(GLuint background, GLuint personagem) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT);
     // -------------------------- background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, background);
	glBegin(GL_TRIANGLE_FAN);// quadrado do tamanho da tela
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(windowW, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(windowW, windowH, 0);
	glTexCoord2f(0, 1); glVertex3f(0, windowH, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

    // -------------------- Personagem
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, personagem);
	glBegin(GL_TRIANGLE_FAN); // PERSONAGEM
	glTexCoord2f(0, 0); glVertex3f(X, Y, 0);
	glTexCoord2f(1, 0); glVertex3f(X + comp, Y, 0);
	glTexCoord2f(1, 1); glVertex3f(X + comp, Y + alt, 0);
	glTexCoord2f(0, 1); glVertex3f(X, Y + alt, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

     // Desenha a fase
    glColor3f(0.5f, 0.5f, 0.5f);
    drawInimigoLevel1();

    // Desenha os tiros
    for (int i = 0; i < 4; i++) {
        drawTiro(i);
    }

    glutSwapBuffers();
}

void updateScene(int value) {
    for (int i = 0; i < 4; i++) {
        updateTiro(i);
    }

    if (pause == false) {
        if (esq == true) {
            X = X - 10;
        }
        else if (dir == true) {
            X = X + 10;
        }
        if (cima == true) {
            Y = Y + 10;
        }
        else if (baixo == true) {
            Y = Y - 10;
        }
        if (X < 0) {
            esq = false;
            X = 0;
        }
        else if (X > windowW - comp) {
            dir = false;
            X = windowW - comp;

        }
        if (Y < 0) {
            baixo = false;
            Y = 0;
        }
        else if (Y > windowH - alt) {
            cima = false;;
            Y = windowH - alt;

        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateScene, 0);
}

void renderSceneJogando(GLuint fundo, GLuint personagem) {
    renderCenaFase1(fundo, personagem);
}
