#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <iostream>
#include <GL/glu.h>

// Variáveis para controlar a posição da câmera
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;

// Variáveis para controlar o ângulo de visão da câmera
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;

// Variáveis para controlar o movimento do mouse
bool mouseLeftDown = false;
int prevMouseX = 0;
int prevMouseY = 0;

//Configuracoes das luzes
bool light1Enabled = false;

GLfloat light1Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light1Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light1Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light1Position[] = { 0.0f, 5.0f, 0.0f, 1.0f };

// Função para definir as propriedades do material
void setMaterialProperties(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[]) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    // Você pode ajustar os valores abaixo para controlar o brilho especular
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
}

void drawBackyardBench(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Desenhar o assento do banco
    GLfloat seatAmbient[] = { 0.7f, 0.4f, 0.2f, 1.0f };
    GLfloat seatDiffuse[] = { 0.7f, 0.4f, 0.2f, 1.0f };
    GLfloat seatSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    setMaterialProperties(seatAmbient, seatDiffuse, seatSpecular);

    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    glScalef(1.5f, 0.1f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenhar o encosto do banco
    GLfloat backrestAmbient[] = { 0.6f, 0.4f, 0.2f, 1.0f };
    GLfloat backrestDiffuse[] = { 0.6f, 0.4f, 0.2f, 1.0f };
    GLfloat backrestSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    setMaterialProperties(backrestAmbient, backrestDiffuse, backrestSpecular);

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, -0.25f);
    glScalef(1.5f, 1.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void drawSofa(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Desenhar o quadrado lateral esquerdo
    glColor3f(0.6f, 0.4f, 0.2f); // Cor marrom para o quadrado lateral
    glPushMatrix();
    glTranslatef(-0.35f, 0.1f, 0.0f); // Posição do quadrado lateral esquerdo
    glScalef(0.2f, 0.8f, 1.0f); // Escala do quadrado lateral
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenhar o quadrado lateral direito
    glColor3f(0.6f, 0.8f, 0.2f); // Cor marrom para o quadrado lateral
    glPushMatrix();
    glTranslatef(0.35f, 0.1f, 0.0f); // Posição do quadrado lateral direito
    glScalef(0.2f, 0.8f, 1.0f); // Escala do quadrado lateral
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenhar o assento
    glColor3f(0.6f, 0.4f, 0.9f); // Cor marrom para o assento
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // Posição do assento
    glRotatef(0.0f, 0.0f, -2.0f, 0.0f); // Inclinação do encosto
    glScalef(0.5f, 0.3f, 1.0f); // Escala do assento
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenhar o encosto
    glColor3f(0.2f, 0.4f, 0.2f); // Cor marrom para o encosto
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.5f); // Posição do encosto
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f); // Inclinação do encosto
    glScalef(0.5f, 1.0f, 0.1f); // Escala do encosto
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void setupLighting() {
    // Ativar iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configurar a posição e cor da luz
    GLfloat light_position[] = {0.0f, 1.0f, 0.0f, 1.0f}; // Posição da luz
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Componente ambiente da luz
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Componente difusa da luz
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Componente especular da luz

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void drawLamp() {
    // Desenhar a base do lustre
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Cor da base (cinza)
    glTranslatef(0.0f, 0.1f, 0.0f); // Posição da base em relação à origem
    glScalef(0.1f, 0.1f, 0.1f); // Escala da base
    glutSolidCube(1.0); // Tamanho da base
    glPopMatrix();

    // Desenhar o suporte do lustre
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Cor do suporte (cinza)
    glTranslatef(0.0f, 0.4f, 0.0f); // Posição do suporte em relação à base
    glScalef(0.02f, 0.4f, 0.02f); // Escala do suporte
    glutSolidCube(1.0); // Tamanho do suporte
    glPopMatrix();

    // Desenhar a parte superior do lustre
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Cor da parte superior (cinza)
    glTranslatef(0.0f, 0.8f, 0.0f); // Posição da parte superior em relação à base
    glScalef(0.08f, 0.08f, 0.08f); // Escala da parte superior
    glutSolidSphere(1.0, 10, 10); // Tamanho e detalhe da parte superior
    glPopMatrix();
}

void drawPlasmaTV(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Desenhar a tela da TV
    glColor3f(0.0f, 0.0f, 0.0f); // Cor preta para a tela
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.93f); // Posição da tela (no centro da base)
    glScalef(0.8f, 0.6f, 0.05f); // Escala da tela
    glutSolidCube(1.0f);
    glPopMatrix();

    //Desenhar o suporte da TV
    glColor3f(0.4f, 0.4f, 0.4f); // Cor cinza para o suporte
    glPushMatrix();
    glTranslatef(0.0f, -0.0f, -0.968f); // Posição do suporte (abaixo da base)
    glScalef(0.1f, 0.2f, 0.05f); // Escala do suporte
    glutSolidCube(1.0f);
    glPopMatrix();

    //Desenhar o quadrado cinza pra ser a tela
    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza para o quadrado
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.90f); // Posição do quadrado (em frente à tela)
    glScalef(0.6f, 0.4f, 0.0f); // Escala do quadrado
    glBegin(GL_QUADS);
    glVertex2f(-0.65f, -0.65f);
    glVertex2f(-0.65f, 0.65f);
    glVertex2f(0.65f, 0.65f);
    glVertex2f(0.65f, -0.65f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void drawTable(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Desenhar o tampo da mesa
    glColor3f(0.6f, 0.4f, 0.2f);  // Cor marrom para o tampo
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);  // Posição do tampo (acima do centro)
    glScalef(1.5f, 0.1f, 1.0f);  // Escala do tampo
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenhar as pernas da mesa
    glColor3f(0.4f, 0.2f, 0.0f);  // Cor marrom para as pernas
    glPushMatrix();
    glTranslatef(-0.7f, -0.4f, 0.4f);  // Posição da perna 1
    glScalef(0.1f, 1.7f, 0.1f);  // Escala da perna
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -0.4f, 0.4f);  // Posição da perna 2
    glScalef(0.1f, 1.7f, 0.1f);  // Escala da perna
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7f, -0.4f, -0.4f);  // Posição da perna 3
    glScalef(0.1f, 1.7f, 0.1f);  // Escala da perna
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -0.4f, -0.4f);  // Posição da perna 4
    glScalef(0.1f, 1.7f, 0.1f);  // Escala da perna
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void drawFridge(float x, float y, float z) {
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);

	glColor4f(0.8, 0.8, 0.8, 1.0f);
	//um lado da geladeira perto da parede
    glVertex3f(-0.4, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 0.3, -1.0);
    glVertex3f(-0.4, 0.3, -1.0);

	glVertex3f(-0.4, -1.0, -1.0);
	glVertex3f(-0.4, -1.0, -0.4);
	glVertex3f(-0.4, 0.3, -0.4);
	glVertex3f(-0.4, 0.3, -1.0);

	glColor4f(0.7, 0.7, 0.7, 1.0f);
	glVertex3f(-0.4, -1.0, -0.4);
	glVertex3f(-1.0, -1.0, -0.4);
	glVertex3f(-1.0, 0.3, -0.4);
	glVertex3f(-0.4, 0.3, -0.4);

	glColor4f(0.8, 0.8, 0.8, 1.0f);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -0.4);
	glVertex3f(-1.0, 0.3, -0.4);
	glVertex3f(-1.0, 0.3, -1.0);

	glVertex3f(-1.0, 0.3, -1.0);
	glVertex3f(-0.4, 0.3, -1.0);
	glVertex3f(-0.4, 0.3, -0.4);
	glVertex3f(-1.0, 0.3, -0.4);

	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-0.4, -1.0, -1.0);
	glVertex3f(-0.4, -1.0, -0.4);
	glVertex3f(-1.0, -1.0, -0.4);
	glEnd();

	// macaneta da geladeira
	glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.1f, -0.39f);
	glVertex3f(-0.55f, 0.1f, -0.39f);
	glVertex3f(-0.55f, -0.4f, -0.39f);
	glVertex3f(-0.5f, -0.4f, -0.39f);
	glEnd();

	        // Desenhar a linha de divisória
    glColor3f(0.0f, 0.0f, 0.0f); // Cor preta para a linha
    glPushMatrix();
    glTranslatef(-0.7f, -0.2f, -0.649f); // Posição da linha na altura 0.3
    glScalef(0.59f, 0.005f, 0.5f); // Escala da linha (comprimento e espessura)
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Função para desenhar o cubo
void drawCube(float x, float y, float z, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);

    // Face frontal
    glColor4f(r, g, b, 1.0f); // Cor específica do cômodo com opacidade total
    glVertex3f(1.0f, 1.0f, -1.0f); // Topo direito
    glVertex3f(-1.0f, 1.0f, -1.0f); // Topo esquerdo
    glVertex3f(-1.0f, -1.0f, -1.0f); // Base esquerda
    glVertex3f(1.0f, -1.0f, -1.0f); // Base direita

     glColor4f(1, 0, 1, 1.0f);
    // Face traseira
    glVertex3f(1.0, -1.0, 1.0); // Topo direito
    glVertex3f(-1.0, -1.0, 1.0); // Topo esquerdo
    glVertex3f(-1.0, 1.0, 1.0); // Base esquerda
    glVertex3f(1.0, 1.0, 1.0); // Base direita

     glColor4f(0, 1, 1, 1.0f);
    // Face superior
    glVertex3f(1.0, 1.0, 1.0); // Topo direito
    glVertex3f(-1.0, 1.0, 1.0); // Topo esquerdo
    glVertex3f(-1.0, 1.0, -1.0); // Base esquerda
    glVertex3f(1.0, 1.0, -1.0); // Base direita


     glColor4f(1, 1, 0, 1.0f);
    // Face esquerda
    glVertex3f(-1.0, 1.0, 1.0); // Topo direito
    glVertex3f(-1.0, 1.0, -1.0); // Topo esquerdo
    glVertex3f(-1.0, -1.0, -1.0); // Base esquerda
    glVertex3f(-1.0, -1.0, 1.0); // Base direita

    // Face direita
    glVertex3f(1.0, 1.0, -1.0); // Topo direito
    glVertex3f(1.0, 1.0, 1.0); // Topo esquerdo
    glVertex3f(1.0, -1.0, 1.0); // Base esquerda
    glVertex3f(1.0, -1.0, -1.0); // Base direita

    // Face inferior
    glColor4f(r+0.5, g+0.5, b+0.6, 1.0f);
    glVertex3f(1.0, -1.0, -1.0); // Topo direito
    glVertex3f(-1.0, -1.0, -1.0); // Topo esquerdo
    glVertex3f(-1.0, -1.0, 1.0); // Base esquerda
    glVertex3f(1.0, -1.0, 1.0); // Base direita

    glEnd();

    // Habilita o blending para permitir a transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Desenhar porta
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // Cor preta com opacidade reduzida para a porta
    glBegin(GL_QUADS);
    glVertex3f(-0.3f, -1.0f, -1.01f); // Topo esquerdo da porta
    glVertex3f(0.3f, -1.0f, -1.01f); // Topo direito da porta
    glVertex3f(0.3f, -0.0f, -1.01f); // Base direita da porta
    glVertex3f(-0.3f, -0.0f, -1.01f); // Base esquerda da porta
    glEnd();

    // Desabilita o blending após desenhar a porta
    glDisable(GL_BLEND);

	// Desenhar maçaneta da porta
    glColor3f(1.0f, 1.0f, 0.0f); // Cor amarela para a maçaneta
    glPointSize(10.0f); // Tamanho da maçaneta
    glBegin(GL_POINTS);
    glVertex3f(0.2f, -0.5f + cameraY, -1.011f); // Posição da maçaneta
    glEnd();

    glPopMatrix();
}

void drawTree(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Desenhar o tronco da árvore
    glColor3f(0.4f, 0.2f, 0.0f);  // Cor marrom para o tronco
    glPushMatrix();
    glScalef(0.1f, 5.0f, 0.1f);  // Escala do tronco
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenhar a copa da árvore
    glColor3f(0.0f, 0.6f, 0.0f);  // Cor verde para a copa
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);  // Posição da copa (acima do tronco)
    glScalef(1.0f, 1.0f, 1.0f);  // Escala da copa
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();

    glPopMatrix();

    //Arvore quadrada
    glPushMatrix();
    glTranslatef(x+2, y, z+5);

    // Desenhar o tronco da árvore
    glColor3f(0.4f, 0.2f, 0.0f);  // Cor marrom para o tronco
    glPushMatrix();
    glScalef(0.1f, 5.0f, 0.1f);  // Escala do tronco
    glutSolidCube(1.0f);
    glPopMatrix();

    // Desenhar a copa da árvore
    glColor3f(0.0f, 0.6f, 0.0f);  // Cor verde para a copa
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);  // Posição da copa (acima do tronco)
    glScalef(1.0f, 1.0f, 1.0f);  // Escala da copa
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void drawFloor() {
    // Desenhar o chão verde
    glColor3f(0.0f, 0.5f, 0.0f);  // Cor verde
    glPushMatrix();
    glTranslatef(0.0f, -1.1f, 0.0f);  // Posição do plano (abaixo da casa e ligeiramente abaixo do chão original)
    glScalef(40.0f, 0.1f, 40.0f);  // Escala do plano (ajustada para cobrir uma área maior)
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Função para desenhar os cômodos
void drawRooms() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);

    if (light1Enabled) {
        glEnable(GL_LIGHTING); // Ativa a iluminação
        glEnable(GL_LIGHT1);
    } else {
        glDisable(GL_LIGHTING); // Desativa a iluminação
        glDisable(GL_LIGHT1);
    }

    // Cômodo 1 - Vermelho
    //drawCube(-2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

    drawPlasmaTV(-2.0f, 0.0f, 0.0f);
    drawSofa(-2.0f, -0.8f, 0.28f);
    // Cômodo 2 - Verde
    //drawCube(2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Cômodo 3 - Amarelo
    //drawCube(0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 0.0f);

    // Cômodo 4 - Azul
    //drawCube(0.0f, 0.0f, -2.0f, 0.0f, 0.0f, 1.0f);
    drawFridge(0.01f, 0.01f, -1.9999f);
drawLamp();
    drawTree(-4.0f, -1.0f, 0.0f);
    drawTable(-5.0f, -1.0f, 1.8f);
    drawBackyardBench(-5.0f, -1.0f, 0.8f);
    drawFloor();

    glFlush();
    glutSwapBuffers();
}

// Função de redimensionamento da janela
void resize(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 10.0);
}

void handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseLeftDown = true;
            prevMouseX = x;
            prevMouseY = y;
        } else if (state == GLUT_UP) {
            mouseLeftDown = false;
        }
    }
}

void handleMouseMovement(int x, int y) {
    int deltaX = x - prevMouseX;
    int deltaY = y - prevMouseY;

    if (mouseLeftDown) {
        // Atualize o ângulo de visão da câmera com base no movimento do mouse
        cameraAngleY += deltaX * 0.1f;
        cameraAngleX += deltaY * 0.1f;

        glutPostRedisplay();
    }

    // Atualize as posições anteriores do mouse
    prevMouseX = x;
    prevMouseY = y;
}

void handleKeyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            // Movimenta para frente
            cameraX += sin(cameraAngleY * M_PI / 180.0) * 0.1f;
            cameraZ -= cos(cameraAngleY * M_PI / 180.0) * 0.1f;
            break;
        case 's':
        case 'S':
            // Movimenta para trás
            cameraX -= sin(cameraAngleY * M_PI / 180.0) * 0.1f;
            cameraZ += cos(cameraAngleY * M_PI / 180.0) * 0.1f;
            break;
        case 'a':
        case 'A':
            // Movimenta para esquerda
            cameraX -= cos(cameraAngleY * M_PI / 180.0) * 0.1f;
            cameraZ -= sin(cameraAngleY * M_PI / 180.0) * 0.1f;
            break;
        case 'd':
        case 'D':
            // Movimenta para direita
            cameraX += cos(cameraAngleY * M_PI / 180.0) * 0.1f;
            cameraZ += sin(cameraAngleY * M_PI / 180.0) * 0.1f;
            break;
        case 'X':
        case 'x':
            cameraY += 0.1f; // Aumenta a altura da câmera em 0.1 unidades
            break;
        case 'Z':
        case 'z':
            cameraY -= 0.1f; // Aumenta a altura da câmera em 0.1 unidades
            break;
        case '1':
            light1Enabled = !light1Enabled;
            break;
    }

    glutPostRedisplay();
}

void init() {
    glClearColor(0.2f, 0.6f, 0.9f, 1.0f); // Cor de fundo branca
    glEnable(GL_DEPTH_TEST); // Ativar teste de profundidade
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Cubo 3D");

    init();
    glutDisplayFunc(drawRooms);
    glutReshapeFunc(resize);
    glutMouseFunc(handleMouseClick);
    glutMotionFunc(handleMouseMovement);
    glutKeyboardFunc(handleKeyPress);
    glutMainLoop();
    return 0;
}

