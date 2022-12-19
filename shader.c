#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include "shader.h"
/* Loads the content of a file and tries to compile it as the specified shader type. */
static GLuint loadShader(char fileName[], GLenum type)
{
    GLuint shader = glCreateShader(type);

    char *buffer = 0;
    long length;
    FILE *f = fopen(fileName, "r");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        rewind(f);
        buffer = malloc(sizeof(char) * length + 1);
        if (buffer)
        {
            int i = 0;
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                buffer[i] = c;
                i++;
            }

            buffer[i] = 0;

            glShaderSource(shader, 1, (const char *const *)(&buffer), NULL);
            glCompileShader(shader);
            int cs = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &cs);
            if (cs == GL_FALSE)
            {
                int length = 0;
                GLchar il[512];
                glGetShaderInfoLog(shader, 512, &length, il);
                printf("Could not Compile Shader! %s \n %s \n resived shader code: \n %s", fileName, il, buffer);
            }

            free(buffer);
        }
        fclose(f);
    }
    else
    {
        printf("Could not find shader file: %s", fileName);
    }

    return shader;
}

/* Creates a shader structure which contains the gl pointer to the linked program. */
shader createShader(char vertName[], char fragName[])
{
    GLuint vert = loadShader(vertName, GL_VERTEX_SHADER);
    GLuint frag = loadShader(fragName, GL_FRAGMENT_SHADER);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glValidateProgram(prog);

    glDeleteShader(vert);
    glDeleteShader(frag);

    shader s = {prog};
    return s;
}