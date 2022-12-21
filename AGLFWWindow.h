#pragma once
#include <GLFW/glfw3.h>
#include "AFramebuffer.h"

GLFWwindow *initGLFWAndGLEW(char title[], int width, int height, AFramebuffer *dfbo);
