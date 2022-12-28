#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "basicShape.h"
#include "aScene.h"
#include "aList.h"
#include "mat3.h"

#define PI 3.14159265359
#undef max
#undef min

static inline double max(double a, double b)
{
    return a > b ? a : b;
}

static inline double min(double a, double b)
{
    return a < b ? a : b;
}

static GLuint genAALUT()
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    unsigned int width = 362, height = 128;
    double d = 0, m = 0, n = 0, sina, cosa;
    double a = 0, a1, A;
    double dx = 0, x1;
    double dy = 0;
    double Sx = 0;
    double Sy = 0;
    unsigned char data[128][362];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            d = x / (double)(width - 1) * sqrt(2.0) / 2.0;
            a = y / (double)(height - 1) * PI / 4.0;

            if (d > 0)
            {
                if (a > 0)
                {
                    sina = sin(a);
                    cosa = cos(a);
                    dx = d * sina;
                    dy = -d * cosa;
                    Sx = 0.5 + dx;
                    Sy = 0.5 + dy;
                    m = sina / cosa;
                    n = Sy - m * Sx;

                    x1 = Sx + dy * Sy / dx;

                    a1 = max(min(x1, 1), 0);
                    A = m / 2 * (1 - a1 * a1) + n * (1 - a1);
                }
                else
                {
                    A = max(-d + 0.5, 0);
                }
            }
            else
            {
                A = 0.5;
            }
            double As = min(A, 0.5) * 2;
            data[y][x] = (unsigned char)(As * 255);
        }
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    return texture;
}

AScene *createAScene()
{
    AScene *scene = malloc(sizeof(AScene));
    scene->basicShapes = createAList(sizeof(BasicShape));
    scene->glAALUT = genAALUT();
    return scene;
};

void destroyScene(AScene *scene)
{
    destroyShader(scene->shader);

    for (unsigned int i = 0; i < scene->basicShapes->size; i++)
    {
        destroyBasicShape((BasicShape *)scene->basicShapes->data[i]);
    }
    destroyAList(scene->basicShapes);

    free(scene);
}