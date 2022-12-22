#include "svg.h"
#include "vec3.h"
#include "vec2.h"
#include "aVAO.h"
#include "aList.h"

static vec3 *fill, *stroke;

VAO *svgToVbo(AList *svgl)
{
    VAO *vao = createVAO();
    // SVGCommand **ca = svgl->data;
    // vec2 P = {0.0f, 0.0f};

    // // the fill pass.
    // for (unsigned int i = 0; i < svgl->size; i++)
    // {
    //     SVGCommand *svgc = ca[i];

    //     switch (svgc->command)
    //     {
    //     case M:
    //     {
    //         P.x = svgc->parameters[0];
    //         P.y = svgc->parameters[1];
    //         break;
    //     }

    //     case m:
    //     {
    //         P.x += svgc->parameters[0];
    //         P.y += svgc->parameters[1];
    //         break;
    //     }

    //     default:
    //         break;
    //     }
    // }

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