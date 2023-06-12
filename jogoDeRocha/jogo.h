#ifndef JOGO_H
#define JOGO_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <iostream>

void teclaPressionada(unsigned char key, int x, int y);

void teclaSolta(unsigned char key, int x, int y);

void renderSceneJogando(GLuint background, GLuint personagem, GLuint hp4, GLuint hp3, GLuint hp2, GLuint hp1, GLuint hp0, GLuint vitoria, GLuint proxFase, GLuint fundoPerdeu, GLuint menu, bool mouseCimaVenceu, int fase);

void initTiros();

void initPontos();

#endif
