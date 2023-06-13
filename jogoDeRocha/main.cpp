#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <iostream>
#include "telaMenu.h"
#include "jogo.h"

using namespace std;

// Tamanho da janela
int windowWidth = 800;
int windowHeight = 600;
int buttonX = 200;
int buttonY = 50;

int butX = (windowWidth - 200) / 2;
int butY = (windowHeight - 50) / 2;

bool jogando1 = false;
bool jogando2 = false;
bool jogando3 = false;
bool jogando4 = false;
bool menu = true;
bool comoJogar = false;
bool mouseCimaVoltMenu = false;
bool mouseCimaJ = false;
bool mouseCimaCJ = false;
bool mouseCimaVenceu = false;

extern bool win;
extern bool lose;
extern bool podeColidir;
extern int pontos;
extern int hp;
extern float X;
extern float Y;
extern float squareSize;
extern float squarePosX;
extern float squarePosY;

GLuint iniciarTexture;
GLuint comoJogarTexture;
GLuint voltarMenuTexture;
GLuint personagem;
GLuint fundo;
GLuint vitoria;
GLuint menuButton;
GLuint proxFase;
GLuint fundoPerdeu;
GLuint comoJogarFundo;
GLuint tiro;
GLuint moeda;
GLuint hp4;
GLuint hp3;
GLuint hp2;
GLuint hp1;
GLuint hp0;

void teclaPressionada(unsigned char key, int x, int y);
void teclaSolta(unsigned char key, int x, int y);

void updateScene(int value);
void atualizaPontos(int value);

// Funcao para carregar uma textura usando SOIL
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

// Funcao de callback para manipular eventos de redimensionamento de janela
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
        renderSceneComoJogar(voltarMenuTexture, comoJogarFundo, mouseCimaVoltMenu, windowWidth, windowHeight);
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
    } else if(jogando1) {
        if(x >= 550 && x <= 750 &&
            y >= 450 && y <= 500) {
            mouseCimaVenceu = true;
        } else {
            mouseCimaVenceu = false;
        }
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 1);
    } else if(jogando2) {
        if(x >= 550 && x <= 750 &&
            y >= 450 && y <= 500) {
            mouseCimaVenceu = true;
        } else {
            mouseCimaVenceu = false;
        }
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 2);
    } else if(jogando3) {
        if(x >= 550 && x <= 750 &&
            y >= 450 && y <= 500) {
            mouseCimaVenceu = true;
        } else {
            mouseCimaVenceu = false;
        }
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 3);
    } else if(jogando4) {
        if(x >= 550 && x <= 750 &&
            y >= 450 && y <= 500) {
            mouseCimaVenceu = true;
        } else {
            mouseCimaVenceu = false;
        }
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 4);
    }
}

// Funcao de callback para desenhar na tela
void renderScene() {
    if(menu) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneMenu(iniciarTexture, comoJogarTexture, mouseCimaJ, mouseCimaCJ, windowWidth, windowHeight);
    } else if(comoJogar) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneComoJogar(voltarMenuTexture, comoJogarFundo, mouseCimaVoltMenu, windowWidth, windowHeight);
    } else if(jogando1) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 1);
    } else if(jogando2) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 2);
    } else if(jogando3) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 3);
    } else if(jogando4) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        renderSceneJogando(fundo, personagem, hp4, hp3, hp2, hp1, hp0, vitoria, proxFase, fundoPerdeu, menuButton, tiro, moeda, mouseCimaVenceu, 4);
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
        menu = false;
        jogando1 = true;
        jogando2 = false;
        jogando3 = false;
        jogando4 = false;
        cout << "Botao 'Iniciar' clicado!" << endl;
    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 300 && x <= 500 &&
        y >= 375 && y <= 425 && menu) {
        comoJogar = true;
        menu = false;
        jogando1 = false;
        jogando2 = false;
        jogando3 = false;
        jogando4 = false;
        cout << "Botao 'Como jogar' clicado!" << endl;

    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 400 && x <= 600 &&
        y >= 370 && y <= 420 && comoJogar) {
        comoJogar = false;
        menu = true;
        jogando1 = false;
        jogando2 = false;
        jogando3 = false;
        jogando4 = false;
        cout << "Botao 'Voltar para o menu' clicado!" << endl;

    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 550 && x <= 750 &&
        y >= 450 && y <= 500 && (lose || (win && jogando4))) {
        pontos = 0;
        X = 20; Y = 20; //posicao do personagem
        hp = 4;
        podeColidir = true;
        win = false;
        lose = false;
        menu = true;
        comoJogar = false;
        jogando1 = false;
        jogando2 = false;
        jogando3 = false;
        jogando4 = false;
        squareSize = 50.0f;
        squarePosX = (windowWidth - squareSize) / 2;
        squarePosY = (windowHeight - squareSize) / 2;

        cout << "Botao 'MENU DPS QUE EPRDE ou ganha fase 4' clicado!"<<win<< endl;
    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 550 && x <= 750 &&
        y >= 450 && y <= 500 && jogando1) {
        pontos = 0;
        comoJogar = false;
        jogando1 = false;
        jogando2 = true;
        jogando3 = false;
        jogando4 = false;
        X = 20; Y = 20; //posicao do personagem
        hp = 4;
        podeColidir = true;
        menu = false;
        win = false;
        cout << "Botao 'Proxima Fase (3)' clicado!"<<win<< endl;
    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 550 && x <= 750 &&
        y >= 450 && y <= 500 && jogando2) {
        pontos = 0;
        comoJogar = false;
        jogando1 = false;
        jogando2 = false;
        jogando3 = true;
        jogando4 = false;
        X = 20; Y = 20; //posicao do personagem
        hp = 4;
        podeColidir = true;
        menu = false;
        win = false;
        cout << "Botao 'Proxima Fase (2)' clicado!"<<win << endl;
    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= 550 && x <= 750 &&
        y >= 450 && y <= 500 && jogando3) {
        pontos = 0;
        comoJogar = false;
        jogando1 = false;
        jogando2 = false;
        jogando3 = false;
        jogando4 = true;
        X = 20; Y = 20; //posicao do personagem
        hp = 4;
        podeColidir = true;
        menu = false;
        win = false;
        cout << "Botao 'Proxima Fase (2)' clicado!"<<win << endl;
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
    comoJogarFundo     = carregaTextura("fundoComoJogar.png");
    voltarMenuTexture  = carregaTextura("voltar.png");
    fundo              = carregaTextura("space3.png");
    personagem         = carregaTextura("enemy.png");
    vitoria            = carregaTextura("vitoria.png");
    proxFase           = carregaTextura("proxima.png");
    menuButton         = carregaTextura("menu.png");
    fundoPerdeu        = carregaTextura("fundoPerdeu.png");
    tiro               = carregaTextura("tiro.png");
    moeda              = carregaTextura("moeda.png");
    //Textura do hp
    hp4 = carregaTextura("4hp.png");
    hp3 = carregaTextura("3hp.png");
    hp2 = carregaTextura("2hp.png");
    hp1 = carregaTextura("1hp.png");
    hp0 = carregaTextura("0hp.png");
    // Define as fucoes de callback
    glutKeyboardFunc(teclaPressionada);
    glutKeyboardUpFunc(teclaSolta);
    glutDisplayFunc(renderScene);

    glutTimerFunc(0, updateScene, 0);
    glutTimerFunc(0, atualizaPontos, 0);
    glutMouseFunc(handleMouse);
    glutPassiveMotionFunc(moveMouse);

    initTiros();
    initPontos();
    initBombas();
    inicializa();

    // Inicia o loop principal do GLUT
    glutMainLoop();

    return 0;
}
