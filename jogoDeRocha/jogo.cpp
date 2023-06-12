#include "jogo.h"
#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

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
float X = 20;
float Y = 20;
float comp = 103.2;
float alt = 177.9;

//--------------Pontos
float pointSize = 30.0f;
vector<float> pointPosX;
vector<float> pointPosY;
int pontos = 0;

int fase = 0;
//--------------Variaveis de controle
bool pause = false;
bool esq = false;
bool dir = false;
bool cima = false;
bool baixo = false;
bool ponto = false;
bool podeColidir = true;
bool win = false;
bool lose = false;

int hp = 4;

void drawPoints() {
    for (size_t i = 0; i < pointPosX.size(); i++) {
        glBegin(GL_QUADS);
        glVertex2f(pointPosX[i], pointPosY[i]);
        glVertex2f(pointPosX[i] + pointSize, pointPosY[i]);
        glVertex2f(pointPosX[i] + pointSize, pointPosY[i] + pointSize);
        glVertex2f(pointPosX[i], pointPosY[i] + pointSize);
        glEnd();
    }
}

void drawTextPoints() {
    // Config do texto
    glColor3f(1.0f, 1.0f, 1.0f);

    //posição do texto
    float altura = 500;
    float largura = 500;
    glRasterPos2f(largura, altura);

    // Exibe o passo atual na tela
    string text;
    text = to_string(pontos) + " / 100\n";

    float textPosition = altura;
    // Exibe o texto na tela
    for (const char c : text) {
        if (c == '\n') {
            //textPosition = textPosition - 30;
            glRasterPos2f((windowW - 420)/2, textPosition);
        } else {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
    }
}

void initPontos() {
    glColor3f(1.0f, 0.0f, 0.0f);
    // Inicializa os pontos
    pointPosX.push_back(100.0f);
    pointPosY.push_back(200.0f);
}

void contaPonto() {
    if(ponto) {
        pontos += 50;
        drawTextPoints();
        ponto = false;
        if (pontos >= 100) {
            win = true;
            lose = false;
            podeColidir=false;
        }
    }
}

void drawInimigoLevel1() {
    glBegin(GL_QUADS);
    glVertex2f(squarePosX, squarePosY);
    glVertex2f(squarePosX + squareSize, squarePosY);
    glVertex2f(squarePosX + squareSize, squarePosY + squareSize);
    glVertex2f(squarePosX, squarePosY + squareSize);
    glEnd();
}

void desenhaBarraHP(GLuint hp4, GLuint hp3, GLuint hp2, GLuint hp1, GLuint hp0) {
    glEnable(GL_TEXTURE_2D);

    switch(hp) {
        case 4:
            glBindTexture(GL_TEXTURE_2D, hp4);
            break;
        case 3:
            glBindTexture(GL_TEXTURE_2D, hp3);
            break;
        case 2:
            glBindTexture(GL_TEXTURE_2D, hp2);
            break;
        case 1:
            glBindTexture(GL_TEXTURE_2D, hp1);
            break;
        case 0:
            glBindTexture(GL_TEXTURE_2D, hp0);
            break;
        default:
            hp = 4;
            glBindTexture(GL_TEXTURE_2D, hp4);
            break;
    }
    glColor3f(1.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0); glVertex3f(50, 500, 0);
    glTexCoord2f(1, 0); glVertex3f(250, 500, 0);
    glTexCoord2f(1, 1); glVertex3f(250, 550, 0);
    glTexCoord2f(0, 1); glVertex3f(50, 550, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
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

void ficaInvuneravel(int value) {
    podeColidir = true;
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
    if ((bulletPosX[index] >= X && bulletPosX[index] <= X + comp && bulletPosY[index] >= Y && bulletPosY[index] <= Y + alt) && podeColidir) {
        // O tiro colidiu com o personagem
        printf("COLIDIU");
        podeColidir = false;
        if (hp == 0 ) {
            lose = true;
            win = false;
        }
        else hp--;
        if (!podeColidir) {
            glutTimerFunc(1000, ficaInvuneravel, 0);
        }
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
        case 87: //w
        case 119: //W
            cima = false;
            break;

        case 83: //s
        case 115: //S
            baixo = false;
            break;

        case 65: //a
        case 97: //A
            esq = false;
            break;

        case 68: //d
        case 100: //D
            dir = false;
            break;;

        /*case 80: //P
            printf("SAI no P");
            break;
        case 68: //p
            printf("SAI no d");
            break;
        default:
            break;*/
    }
    glutPostRedisplay();
}

void drawButtonn(GLuint texture, int x, int y, int width, int height, bool mouseCima) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (mouseCima) {
        glColor3f(1.0f, 0.0f, 1.0f); // Cor rosa se o mouse estiver em cima do botão
    } else {
        glColor3f(1.0f, 1.0f, 1.0f); // Cor branca se o mouse não estiver em cima do botão
    }

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0); glVertex3f(x, y, 0);
    glTexCoord2f(1, 0); glVertex3f(x + width, y, 0);
    glTexCoord2f(1, 1); glVertex3f(x + width, y + height, 0);
    glTexCoord2f(0, 1); glVertex3f(x, y + height, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void venceu(GLuint vitoria, GLuint proxFase, bool mouseCimaVenceu) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(128, 128, 128);
    // -------------------------- background
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, vitoria);
    glBegin(GL_TRIANGLE_FAN);// quadrado do tamanho da tela
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(windowW, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(windowW, windowH, 0);
    glTexCoord2f(0, 1); glVertex3f(0, windowH, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Desenhar o botão por cima da textura de fundo
    glEnable(GL_COLOR_MATERIAL); // Reabilitar o uso de cores
    drawButtonn(proxFase, 550, 100, 200, 50, mouseCimaVenceu);
    glDisable(GL_COLOR_MATERIAL); // Desabilitar o uso de cores

    glutSwapBuffers();
}

void perdeu(GLuint fundoPerdeu, GLuint menu, bool mouseCimaVenceu) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(128, 128, 128);
    // -------------------------- background
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fundoPerdeu);
    glBegin(GL_TRIANGLE_FAN);// quadrado do tamanho da tela
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(windowW, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(windowW, windowH, 0);
    glTexCoord2f(0, 1); glVertex3f(0, windowH, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Desenhar o botão por cima da textura de fundo
    glEnable(GL_COLOR_MATERIAL); // Reabilitar o uso de cores
    drawButtonn(menu, 550, 100, 200, 50, mouseCimaVenceu);
    glDisable(GL_COLOR_MATERIAL); // Desabilitar o uso de cores

    glutSwapBuffers();
}

void renderCenaFase1(GLuint background, GLuint personagem, GLuint hp4, GLuint hp3, GLuint hp2, GLuint hp1, GLuint hp0, GLuint vitoria, GLuint proxFase, GLuint fundoPerdeu, GLuint menu, bool mouseCimaVenceu) {
    if (win){
        podeColidir = false;
        venceu(vitoria, proxFase,mouseCimaVenceu);
    } else if(lose){
        podeColidir = false;
        perdeu(fundoPerdeu, menu, mouseCimaVenceu);
    } else {
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
        if (!podeColidir) {
            glColor3f(1.0f, 0.0f, 1.0f);
        }
        glBegin(GL_TRIANGLE_FAN); // PERSONAGEM
        glTexCoord2f(0, 0); glVertex3f(X, Y, 0);
        glTexCoord2f(1, 0); glVertex3f(X + comp, Y, 0);
        glTexCoord2f(1, 1); glVertex3f(X + comp, Y + alt, 0);
        glTexCoord2f(0, 1); glVertex3f(X, Y + alt, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        if (!podeColidir) glColor3f(1.0f, 1.0f, 1.0f);

        //desenha os pontos.
        drawPoints();
        drawTextPoints();
        //---------------
        desenhaBarraHP(hp4, hp3, hp2, hp1, hp0);
        // Verifica colisao entre o personagem e os pontos
        for (size_t i = 0; i < pointPosX.size(); i++) {
            if (X < pointPosX[i] + pointSize && X + comp > pointPosX[i] && Y < pointPosY[i] + pointSize && Y + alt > pointPosY[i]) {
                printf("Colidiu com o ponto");
                pointPosX.clear();
                pointPosY.clear();
                glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Muda a cor do fundo para azul
                ponto = true;
                contaPonto();
                break; // Interrompe o loop, pois já encontrou uma colisão
            }
        }

         // Desenha a fase
        glColor3f(0.5f, 0.5f, 0.5f);
        drawInimigoLevel1();

        // Desenha os tiros
        for (int i = 0; i < 4; i++) {
            drawTiro(i);
        }
        glutSwapBuffers();
    }
}

void adicionaPonto() {
    // Limpa os pontos existentes
    pointPosX.clear();
    pointPosY.clear();

    float posX = fmod(rand(), (windowW - pointSize));
    float posY = fmod(rand(), (windowH - pointSize));

    pointPosX.push_back(posX);
    pointPosY.push_back(posY);
}

void atualizaPontos(int value) {
    adicionaPonto();

    glutPostRedisplay();
    glutTimerFunc(4000, atualizaPontos, 4000);
}

void updateScene(int value) {
    for (int i = 0; i < 4; i++) {
        updateTiro(i);
    }

    if (pause == false) {
        if (esq == true) {
            X = X - 5;
        }
        else if (dir == true) {
            X = X + 5;
        }
        if (cima == true) {
            Y = Y + 5;
        }
        else if (baixo == true) {
            Y = Y - 5;
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

void renderSceneJogando(GLuint fundo, GLuint personagem, GLuint hp4, GLuint hp3, GLuint hp2, GLuint hp1, GLuint hp0, GLuint vitoria, GLuint proxFase, GLuint fundoPerdeu, GLuint menu, bool mouseCimaVenceu, int fase) {
    fase = fase;
    if(fase == 1){
        renderCenaFase1(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menu, mouseCimaVenceu);
    } else if(fase == 2){
        renderCenaFase1(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menu, mouseCimaVenceu);
    } else if(fase == 3){
        renderCenaFase1(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menu, mouseCimaVenceu);
    }


}
