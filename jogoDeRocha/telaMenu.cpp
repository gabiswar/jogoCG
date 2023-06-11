#include "telaMenu.h"
#include <iostream>

void drawButtonn(GLuint texture, int x, int y, int width, int height, bool mouseCima) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (mouseCima) {
        glColor3f(1.0f, 0.0f, 1.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0); glVertex3f(x, y, 0);
    glTexCoord2f(1, 0); glVertex3f(x + width, y, 0);
    glTexCoord2f(1, 1); glVertex3f(x + width, y + height, 0);
    glTexCoord2f(0, 1); glVertex3f(x, y + height, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void renderSceneMenu(GLuint iniciarTexture, GLuint comoJogarTexture, bool mouseCimaJ, bool mouseCimaCJ, int windowWidth, int windowHeight) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o botão "Iniciar" no centro da tela
    int posicaoX = (windowWidth - 200) / 2;
    int posicaoY = (windowHeight - 50) / 2;

    // Desenha botão iniciar
    drawButtonn(iniciarTexture, posicaoX, posicaoY, 200, 50, mouseCimaJ);

    // Desenha botão como jogar
    drawButtonn(comoJogarTexture, posicaoX, posicaoY - 100, 200, 50, mouseCimaCJ);

    glutSwapBuffers();
}

void renderSceneComoJogar(GLuint voltarMenuTexture, bool mouseCimaVoltMenu, int windowWidth, int windowHeight) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT);

    // Confi do texto
    glColor3f(1.0f, 1.0f, 1.0f);
    float altura = (windowHeight + 200) /2;
    glRasterPos2f((windowWidth - 420)/2 , altura);

    // Exibe o passo atual na tela
    std::string text;
    text += "Passo 1: Mova o personagem usando as teclas:";
    text += "\n\t\t\t\tW -> cima, A -> esquerda, D -> direita.";

    text += "\nPasso 2: Atire no inimigo usando a tecla space.";

    text += "\nPasso 3: Evite os inimigos para nao perder vidas.";

    text += "\nPasso 4: Alcance a saida para completar o nivel.";

    float textPosition = altura;
    // Exibe o texto na tela
    for (const char c : text) {
        if (c == '\n') {
            textPosition = textPosition - 30;
            glRasterPos2f((windowWidth - 420)/2, textPosition);
        } else {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    //desenha botao voltar para o menu
    drawButtonn(voltarMenuTexture, (windowWidth)/2, textPosition - 100 , 200, 50, mouseCimaVoltMenu);

    glutSwapBuffers();
}
