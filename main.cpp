#include <GL/glut.h>
#include <iostream>

// Tamanho da janela
int windowWidth = 800;
int windowHeight = 600;
bool jogando = false;
bool menu = true;
bool comoJogar = false;


// Função para carregar uma textura usando SOIL
/*GLuint loadTexture(const char* filename) {
    GLuint textureID = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0)
    {
        std::cout << "Erro ao carregar a textura: " << SOIL_last_result() << std::endl;
    }

    return textureID;
}*/

// Função para desenhar um botão na tela
void drawButton(int x, int y, int width, int height) {

    if(menu) {
        //glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.0, 0.0, 0.0); // Define a cor vermelha

        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();
        //glDisable(GL_TEXTURE_2D);
    } else if(comoJogar) {
        std::cout<<"entrei";
        //glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.0, 0.0, 0.0); // Define a cor vermelha

        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();
        //glDisable(GL_TEXTURE_2D);
    }
}
void renderSceneMenu() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo como preto
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o botão "Iniciar" no centro da tela
    int buttonWidth = 200;
    int buttonHeight = 50;
    int buttonX = (windowWidth - buttonWidth) / 2;
    int buttonY = (windowHeight - buttonHeight) / 2;

    //desenha botão iniciar
    drawButton(buttonX, buttonY, buttonWidth, buttonHeight);

    //desenha botão como jogar
    drawButton(buttonX, buttonY - 100, buttonWidth, buttonHeight);

    glutSwapBuffers();
}

void renderSceneComoJogar() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo como preto
    glClear(GL_COLOR_BUFFER_BIT);

    // Configurações de exibição de texto
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(100.0f, windowHeight - 100.0f);

    // Exibe o passo atual na tela
    std::string text;
    text += "Passo 1: Mova o personagem usando as teclas:";
    text += "\n\t \t \t \t \t \t \t \tW -> cima, A -> esquerda, D -> direita.";

    text += "\nPasso 2: Atire no inimigo usando a tecla space.";

    text += "\nPasso 3: Evite os inimigos para não perder vidas.";

    text += "\nPasso 4: Alcance a saída para completar o nível.";

    float textPosition = windowHeight - 100;
    // Exibe o texto na tela
    for (const char c : text) {
        if (c == '\n') {
            textPosition = textPosition - 30;
            glRasterPos2f(100.0f, textPosition);
        } else {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    //desenha botão voltar para o menu
    drawButton(100, textPosition - 100 , 200, 50);

    glutSwapBuffers();

   /* glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Define a cor de fundo como preto
    glClear(GL_COLOR_BUFFER_BIT);



    // Desenha o botão "Iniciar" no centro da tela
    int buttonWidth = 200;
    int buttonHeight = 50;
    int buttonX = (windowWidth - buttonWidth) / 2;
    int buttonY = (windowHeight - buttonHeight) / 2;


    //desenha botão voltar
    drawButtonMenu(buttonX - 50, buttonY - 200, buttonWidth, buttonHeight);

    glutSwapBuffers();*/
}

void renderSceneJogando() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Define a cor de fundo como preto
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o botão "Iniciar" no centro da tela
    int buttonWidth = 200;
    int buttonHeight = 50;
    int buttonX = (windowWidth - buttonWidth) / 2;
    int buttonY = (windowHeight - buttonHeight) / 2;

    //desenha botão voltar
    drawButton(buttonX - 20, buttonY - 200, buttonWidth, buttonHeight);

    glutSwapBuffers();
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
    if((button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= (windowWidth - 200) / 2 && x <= (windowWidth + 200) / 2 &&
        y >= (windowHeight - 50) / 2 && y <= (windowHeight + 50) / 2) && menu) {
        comoJogar = false;
        jogando = true;
        menu = false;
        std::cout << "Botão 'Iniciar' clicado!" << std::endl;
        // Implemente o código para iniciar o jogo aqui
    }

    //std::cout<<"Cima:"<<((windowHeight - 50)/2)<<std::endl;

    // Verifica se o botão "Como jogar" foi clicado vai pra outra tela
    //std::cout<<"x: "<<x<<" y:"<<y<<std::endl;
    if((button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        x >= (windowWidth - 200) / 2 && x <= (windowWidth + 200) / 2 &&
        y >= (windowHeight + 150) / 2 && y <= (windowHeight + 250) / 2) && menu) {
        comoJogar = true;
        jogando = false;
        menu = false;
        std::cout << "Botão 'Como jogar' clicado!" << std::endl;
        // Implemente o código para iniciar o jogo aqui
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

int main(int argc, char** argv)
{
    // Inicialização do GLUT e criação da janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Meu Jogo 2D");

    // Carrega a textura do botão
    //buttonTexture = loadTexture("direita.png");

    // Define as funções de callback
    glutDisplayFunc(renderScene);
    glutMouseFunc(handleMouse);
    inicializa();

    // Inicia o loop principal do GLUT
    glutMainLoop();

    return 0;
}
