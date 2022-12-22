#pragma once

#include "aArrayList.h"
#include "aVAO.h"
#include "vec3.h"

// Most wont be implementet though.
enum svgcom
{
    M,
    m,
    Z,
    z,
    L,
    l,
    H,
    h,
    V,
    v,
    C,
    c,
    S,
    s,
    Q,
    q,
    T,
    t,
    A,
    a
};

typedef struct SVGCommand
{
    // the the svg command
    enum svgcom command;
    // the data for the svg command
    float *parameters;
} SVGCommand;

//  @param *svgl must be a list of SVGCommada.
VAO *svgToVbo(AArrayList *svgl);

void svgSetFill(vec3 *color);
void svgSetStroke(vec3 *color);
