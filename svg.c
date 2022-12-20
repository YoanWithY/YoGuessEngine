#include "svg.h"
#include "vec3.h"
#include "vec2.h"
#include "aVAO.h"

static vec3 *fill, *stroke;

VAO svgToVbo(AList *svgl)
{
    // vec2 P = {0, 0};
    // SVGCommand **svgcom = (SVGCommand **)svgl->data;

    // VAO vao = createVAO();

    // for (unsigned int i = 0; i < svgl->size; i++)
    // {
    //     SVGCommand *com = svgcom[i];
    // }
    return createVAO();
}

void svgSetFill(vec3 *color)
{
    fill = color;
};

void svgSetStroke(vec3 *color)
{
    stroke = color;
};