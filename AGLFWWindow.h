#pragma once
#include <GLFW/glfw3.h>
#include "AFramebuffer.h"

GLFWwindow *initGLFWAndGLEW(char title[], int width, int height, AFramebuffer *dfbo, void (*key_callback)(GLFWwindow *window, int key, int scancode, int action, int mods));
