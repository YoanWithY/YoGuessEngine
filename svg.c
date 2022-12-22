#include "svg.h"
#include "vec3.h"
#include "vec2.h"
#include "aVAO.h"
#include "aArrayList.h"

static vec3 *fill, *stroke;

VAO *svgToVbo(AArrayList *svgl)
{
    VAO *vao = createVAO();
    return vao;
}

void svgSetFill(vec3 *color)
{
    fill = color;
};

void svgSetStroke(vec3 *color)
{
    stroke = color;
};