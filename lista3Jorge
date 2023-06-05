#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include <math.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#define navelarg 20
#define navealt 40
#define navex 20
#define navey 40
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int windowH = 1000;
int windowW = 1000;




float X = 450;
float Y = 20;
float comp = 103.2;
float alt = 177.9;

float Xinimigo = 400;
float Yinimigo = 780;
float compinimigo = 225;
float altinimigo = 225;

float velX = 10;

int mouseX = 0, mouseY = 0;

int cont = 0;
bool esq = false;
bool dir = false;
bool cima = false;
bool baixo = false;

bool parou = true;

bool left_down = false;
bool right_down = false;
bool fundo1 = true;
bool pause = false;
bool pisca = false;

bool colisaoPerso() {
   if (Y + alt >= Yinimigo+30 && Y <= Yinimigo + altinimigo+30 && X <= Xinimigo + compinimigo-30 && X + comp > Xinimigo+30) return true;
   else return false;
}


GLuint plane;
GLuint enemy;
GLuint fundo;
GLuint carregaFundo(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
        arquivo,        // ⬅️ do parâmetro
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (idTextura == 0) {
        printf("Erro carregando a textura: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

void desenhaFundo(int valorQualquer) {
	if (fundo1) {
		fundo1 = false;
		fundo = carregaFundo("space4.png");
	}
	else {
		fundo1 = true;
		fundo = carregaFundo("space3.png");
	}
	glutTimerFunc(100, desenhaFundo, 60);
}
void desenhaCena() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (pisca == false) {
		glColor3f(1, 1, 1);
	}
	else {
	glColor3f(1, 0, 0);
		pisca = false;
	}
	// -------------------------- background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fundo);
	glBegin(GL_TRIANGLE_FAN);// quadrado do tamanho da tela
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(windowW, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(windowW, windowH, 0);
	glTexCoord2f(0, 1); glVertex3f(0, windowH, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// -------------------- Personagem
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, plane);
	glBegin(GL_TRIANGLE_FAN); // PERSONAGEM
	glTexCoord2f(0, 0); glVertex3f(X, Y, 0);
	glTexCoord2f(1, 0); glVertex3f(X + comp, Y, 0);
	glTexCoord2f(1, 1); glVertex3f(X + comp, Y + alt, 0);
	glTexCoord2f(0, 1); glVertex3f(X, Y + alt, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	///------------------------------------------------------
	//Inimigo



	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, enemy);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(Xinimigo, Yinimigo, 0);
	glTexCoord2f(1, 0); glVertex3f(Xinimigo + compinimigo, Yinimigo, 0);
	glTexCoord2f(1, 1); glVertex3f(Xinimigo + compinimigo, Yinimigo + altinimigo, 0);
	glTexCoord2f(0, 1); glVertex3f(Xinimigo, Yinimigo + altinimigo, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//
	// ----------------------------------------------------
	if (left_down == true) {
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1,0,0.5);
		glVertex2f(mouseX, windowH-mouseY);
		for (int i=0;i<=25;i++){
			float angulo = 2.0f * M_PI * (float)i/25.0f;
			float px = (float)mouseX + 100.0f * cos(angulo);
			float py = (float)(windowH-mouseY) + 100.0f * sin(angulo);
			glVertex2f(px, py);
		}
		glEnd();
	}
	if (right_down == true) {
		glColor3f(1,0,0.5);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(mouseX-50, windowH-(mouseY+50));
		glVertex2f(mouseX+50, windowH-(mouseY+50));
		glVertex2f(mouseX+50, windowH-(mouseY-50));
		glVertex2f(mouseX-50, windowH-(mouseY-50));
		glEnd();
	}

	glutSwapBuffers();
}


void atualizaCena(int valorqualquer) {
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
            dir = false;;
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
        //=============================
        //movimento inimigo
        Xinimigo = Xinimigo + velX;
        if (Xinimigo < 0) {
            velX = -velX;
        }
        else if (Xinimigo > windowW - compinimigo) {
            velX = -velX;
        }
        if (colisaoPerso()) {
            pisca = true;

        }

	if (esq == false && dir == false && parou == false) {
		plane = carregaFundo("front_plane.png");
		parou = true;
	}
    }
    //===========================
    glutPostRedisplay();
    glutTimerFunc(33, atualizaCena, 0);
}



void inicializa() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    plane = carregaFundo("front_plane.png");
    enemy = carregaFundo("enemy.png");
    fundo = carregaFundo("space3.png");


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void redimensionada(int width, int height) {
    if (width > height) {
        glViewport(0, 0, height, height);
    }
    else {
        glViewport(0, 0, width, width);
    }
	glViewport(0, 0, width, height);
	windowH = height;
	windowW = width;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void teclaPressionada(unsigned char key, int x, int y) {
    // vê qual tecla foi pressionada
    switch (key) {
    case 80: //P
        if (pause == false) {
            pause = true;
        }
        else pause = false;
        break;
    case 112: //p
        if (pause == false) {
            pause = true;
        }
        else pause = false;
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
		parou = false;
		plane = carregaFundo("full_left_plane.png");
    	}
        break;
    case 68: //d
    case 100: //D
    	if(dir == false) {
		esq = false;
		dir = true;
		parou = false;
		plane = carregaFundo("full_right_plane.png");
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
//void TeclasEspeciais(int key, int x, int y)
//{
//    if (key == GLUT_KEY_LEFT) {
//        esq = true;
//        dir = false;
//    }
//    if (key == GLUT_KEY_RIGHT) {
//        dir = true;
//        esq = false;
//    }
//    if (key == GLUT_KEY_DOWN) {
//        dir = false;
//        esq = false;
//    }
//    if (key == GLUT_KEY_UP) {
//        dir = false;
//        esq = false;
//    }
//    glutPostRedisplay();
//}
void teclaSolta(unsigned char key, int x, int y)
{
    switch (key) {
    case 87: //w
    case 119: //W
        cima = false;
        baixo = false;
        break;
    case 83: //s
    case 115: //S
        cima = false;
        baixo = false;
        break;
    case 65: //a
    case 97: //A
    	if (esq == true) {
		esq = false;
		dir = false;
    	}
        break;
    case 68: //d
    case 100: //D
    	if (dir == true) {    	
		esq = false;
		dir = false;
    	}
        break;
    }
    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y){
	if (state == GLUT_DOWN && (left_down == false || right_down == false)) {
		mouseX = x;
		mouseY = y;
		if (button == GLUT_LEFT_BUTTON) {
			left_down =  true;
		}
		if (button == GLUT_RIGHT_BUTTON) {
			right_down = true;
		}
	}
	if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			left_down =  false;
		}
		if (button == GLUT_RIGHT_BUTTON) {
			right_down = false;
		}
	}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(windowW, windowH);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Jorge Hiroki de Castro Sato");


    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensionada);
    glutKeyboardFunc(teclaPressionada);
    glutKeyboardUpFunc(teclaSolta);
    glutMouseFunc(mouseClick);
    //glutSpecialFunc(TeclasEspeciais);
    glutTimerFunc(0, atualizaCena, 33);
    //glutTimerFunc(100, desenhaFundo, 60);
    inicializa();

    //criaListaAnelQuadrado();/
    glutMainLoop();
    return 0;
}
