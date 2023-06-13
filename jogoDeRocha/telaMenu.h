#ifndef TELAMENU_H
#define TELAMENU_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <iostream>

void renderSceneMenu(GLuint iniciarTexture, GLuint comoJogarTexture, bool mouseCimaJ, bool mouseCimaCJ, int windowWidth, int windowHeight);

void renderSceneComoJogar(GLuint voltarMenuTexture, GLuint fundoComoJogar, bool mouseCimaVoltMenu, int windowWidth, int windowHeight);

#endif
