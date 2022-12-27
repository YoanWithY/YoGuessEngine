#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include <math.h>
#include "aShader.h"

/* Loads the content of a file and tries to compile it as the specified AShader type. */
static GLuint loadShader(char *fileName, GLenum type)
{
    GLuint shader = glCreateShader(type);

    long length;
    FILE *f;
    fopen_s(&f, fileName, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        rewind(f);
        char *buffer = malloc(sizeof(char) * length + 1);

        int i = 0;
        char c;
        while ((c = fgetc(f)) != EOF)
        {
            buffer[i] = c;
            i++;
        }
        if (i < length)
        {
            buffer[i] = 0;
        }
        else
        {
            buffer[length] = 0;
        }

        glShaderSource(shader, 1, (const char *const *)(&buffer), NULL);
        glCompileShader(shader);
        int cs = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &cs);
        if (cs == GL_FALSE)
        {
            printf_s("Could not Compile Shader! %s\n", fileName);
            int length = 0;
            GLchar il[512];
            glGetShaderInfoLog(shader, 512, &length, il);
            printf_s("%s \n resived shader code: \n %s\n", il, buffer);
        }

        free(buffer);
    }
    else
    {
        printf_s("Could not find shader file: %s", fileName);
    }

    fclose(f);

    return shader;
}

AShader *createShader(char *vertName, char *fragName)
{
    AShader *shader = malloc(sizeof(AShader));
    GLuint vert = loadShader(vertName, GL_VERTEX_SHADER);
    GLuint frag = loadShader(fragName, GL_FRAGMENT_SHADER);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glValidateProgram(prog);

    glDeleteShader(vert);
    glDeleteShader(frag);

    shader->prog = prog;
    shader->glSceneScale = glGetUniformLocation(prog, "sceneScale");
    shader->glTMat = glGetUniformLocation(prog, "tMat");
    shader->glRotAdd = glGetUniformLocation(prog, "rotAdd");

    return shader;
}

void destroyShader(AShader *shader)
{
    glDeleteProgram(shader->prog);
    free(shader);
}