#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <iostream>
#include "telaMenu.h"

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
GLuint plane;
GLuint enemy;
GLuint fundo;

void teclaPressionada(unsigned char key, int x, int y);
void teclaSolta(unsigned char key, int x, int y);

// Fun��o para carregar uma textura usando SOIL
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


// Função de callback para manipular eventos de redimensionamento de janela
void reshape(int width, int height) {
    // Define o tamanho da viewport para corresponder ao tamanho da janela
    glViewport(0, 0, windowWidth, windowHeight);

    // Mantém o tamanho da janela fixo
    glutReshapeWindow(windowWidth, windowHeight);
}

void moveMouse(int x, int y) {
    if(comoJogar) {
        if(x >= 400 && x <= 600 &&
            y >= 370 && y <= 420) {
            mouseCimaVoltMenu = true;
        } else {
            mouseCimaVoltMenu = false;
        }
        renderSceneComoJogar(voltarMenuTexture, mouseCimaVoltMenu, windowWidth, windowHeight);
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
        renderSceneMenu(iniciarTexture, comoJogarTexture, mouseCimaJ, mouseCimaCJ, windowWidth, windowHeight);
    }
}

// Funcao de callback para desenhar na tela
void renderScene() {
    if(menu) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneMenu(iniciarTexture, comoJogarTexture, mouseCimaJ, mouseCimaCJ, windowWidth, windowHeight);
    } else if(comoJogar) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneComoJogar(voltarMenuTexture, mouseCimaVoltMenu, windowWidth, windowHeight);
    } else if(jogando) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //renderSceneJogando();
    }


}

// Funcao de callback para lidar com eventos do mouse
void handleMouse(int button, int state, int x, int y) {
    // Verifica se o botao "Iniciar" foi clicado vai pro jogando
    cout<<"x: "<< x<< " y: "<<y<<endl;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 300 && x <= 500 &&
        y >= 275 && y <= 325 && menu) {
        comoJogar = false;
        jogando = true;
        menu = false;
        cout << "Botao 'Iniciar' clicado!" << endl;
    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 300 && x <= 500 &&
        y >= 375 && y <= 425 && menu) {
        comoJogar = true;
        jogando = false;
        menu = false;
        cout << "Botao 'Como jogar' clicado!" << endl;

    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 400 && x <= 600 &&
        y >= 370 && y <= 420 && comoJogar) {
        comoJogar = false;
        jogando = false;
        menu = true;
        cout << "Botao 'Voltar para o menu' clicado!" << endl;

    }
}

void inicializa() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Ajuste a escala da proje��o para abranger toda a janela
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Inicializacao do GLUT e criacao da janela
    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Jogo 2D");

    glutReshapeFunc(reshape);

    //Carrega a textura do botao
    iniciarTexture     = carregaTextura("jogar.png");
    comoJogarTexture   = carregaTextura("comoJogar.png");
    voltarMenuTexture  = carregaTextura("voltar.png");
    //plane              = carregaFundo("front_plane.png");
    //enemy              = carregaFundo("enemy.png");
    //fundo              = carregaFundo("space3.png");

    // Define as fucoes de callback
    glutKeyboardFunc(teclaPressionada);
    glutKeyboardUpFunc(teclaSolta);
    glutDisplayFunc(renderScene);
    glutMouseFunc(handleMouse);
    glutPassiveMotionFunc(moveMouse);
    inicializa();

    // Inicia o loop principal do GLUT
    glutMainLoop();

    return 0;
}
