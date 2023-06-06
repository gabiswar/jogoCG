#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// Tamanho da janela
int windowWidth = 800;
int windowHeight = 600;
int buttonX = 200;
int buttonY = 50;

int butX = (windowWidth - 200) / 2;
int butY = (windowHeight - 50) / 2;

bool jogando = false;
bool menu = true;
bool comoJogar = false;
bool mouseCimaVoltMenu = false;
bool mouseCimaJ = false;
bool mouseCimaCJ = false;

GLuint iniciarTexture;
GLuint comoJogarTexture;
GLuint voltarMenuTexture;

// Função para carregar uma textura usando SOIL
GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

// Função para desenhar um botão na tela
void drawButton(GLuint texture, int x, int y, int width, int height, bool mouseCima) {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(mouseCima) {
       glColor3f(1.0f, 0.0f, 1.0f);
    } else {
       glColor3f(1.0f, 1.0f, 1.0f);
    }
    buttonX = width;
    buttonY = height;

    if(menu) {
        //iniciar e como jogar
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(x, y, 0);
        glTexCoord2f(1, 0); glVertex3f(x + width, y, 0);
        glTexCoord2f(1, 1); glVertex3f(x + width, y + height, 0);
        glTexCoord2f(0, 1); glVertex3f(x, y + height, 0);
        glEnd();
    } else if(comoJogar) {

        glBegin(GL_TRIANGLE_FAN);
        //botão voltar para o Menu
        glTexCoord2f(0, 0); glVertex3f(x, y, 0);
        glTexCoord2f(1, 0);  glVertex3f(x + width, y, 0);
        glTexCoord2f(1, 1); glVertex3f(x + width, y + height, 0);
        glTexCoord2f(0, 1); glVertex3f(x, y + height, 0);
        glEnd();
    }
        glDisable(GL_TEXTURE_2D);
}

void renderSceneMenu() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o botão "Iniciar" no centro da tela
    butX = (windowWidth - 200) / 2;
    butY = (windowHeight - 50) / 2;

    //desenha botão iniciar
    drawButton(iniciarTexture, butX, butY, 200, 50, mouseCimaJ);

    //desenha botão como jogar
    drawButton(comoJogarTexture, butX, butY - 100, 200, 50, mouseCimaCJ);

    glutSwapBuffers();
}

void renderSceneComoJogar() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT);

    // Configurações de exibição de texto
    glColor3f(1.0f, 1.0f, 1.0f);
    float altura = (windowHeight + 200) /2;
    glRasterPos2f((windowWidth - 420)/2 , altura);

    // Exibe o passo atual na tela
    std::string text;
    text += "Passo 1: Mova o personagem usando as teclas:";
    text += "\n\t\t\t\tW -> cima, A -> esquerda, D -> direita.";

    text += "\nPasso 2: Atire no inimigo usando a tecla space.";

    text += "\nPasso 3: Evite os inimigos para não perder vidas.";

    text += "\nPasso 4: Alcance a saída para completar o nível.";

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

    //desenha botão voltar para o menu
    drawButton(voltarMenuTexture, (windowWidth)/2, textPosition - 100 , 200, 50, mouseCimaVoltMenu);

    glutSwapBuffers();
}

void renderSceneJogando() {
    //TODO
}

void moveMouse(int x, int y) {
    if(comoJogar) {
        if(x >= 400 && x <= 600 &&
            y >= 370 && y <= 420) {
            mouseCimaVoltMenu = true;
        } else {
            mouseCimaVoltMenu = false;
        }
        renderSceneComoJogar();
    } else if(menu) {
        if(x >= butX && x <= butX+200 &&
            y >= butY && y <= butY+50) {
            mouseCimaJ = true;
        } else {
            mouseCimaJ = false;
        }

        if(x >= butX && x <= butX+200 &&
            y >= butY+100 && y <= butY+150) {
            mouseCimaCJ = true;
        } else {
            mouseCimaCJ = false;
        }
        renderSceneMenu();
    }
}

// Função de callback para desenhar na tela
void renderScene() {
    if(menu) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneMenu();
    } else if(comoJogar) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneComoJogar();
    } else if(jogando) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneJogando();
    }


}

// Função de callback para lidar com eventos do mouse
void handleMouse(int button, int state, int x, int y) {
    // Verifica se o botão "Iniciar" foi clicado vai pro jogando
    cout<<"x: "<< x<< " y: "<<y<<endl;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 300 && x <= 500 &&
        y >= 275 && y <= 325 && menu) {
        comoJogar = false;
        jogando = true;
        menu = false;
        std::cout << "Botão 'Iniciar' clicado!" << std::endl;
    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 300 && x <= 500 &&
        y >= 375 && y <= 425 && menu) {
        comoJogar = true;
        jogando = false;
        menu = false;
        std::cout << "Botão 'Como jogar' clicado!" << std::endl;

    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 400 && x <= 600 &&
        y >= 370 && y <= 420 && comoJogar) {
        comoJogar = false;
        jogando = false;
        menu = true;
        std::cout << "Botão 'Voltar para o menu' clicado!" << std::endl;

    }
}

void inicializa() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Ajuste a escala da projeção para abranger toda a janela
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Inicialização do GLUT e criação da janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Meu Jogo 2D");

    //Carrega a textura do botão
    iniciarTexture     = carregaTextura("jogar.png");
    comoJogarTexture   = carregaTextura("comoJogar.png");
    voltarMenuTexture  = carregaTextura("voltar.png");

    // Define as funções de callback
    glutDisplayFunc(renderScene);
    glutMouseFunc(handleMouse);
    glutPassiveMotionFunc(moveMouse);
    inicializa();

    // Inicia o loop principal do GLUT
    glutMainLoop();

    return 0;
}
