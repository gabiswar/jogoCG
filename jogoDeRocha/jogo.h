#ifndef JOGO_H
#define JOGO_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <iostream>

void teclaPressionada(unsigned char key, int x, int y);

void teclaSolta(unsigned char key, int x, int y);

void renderSceneJogando(GLuint fundo, GLuint personagem);

void initTiros();

#endif
