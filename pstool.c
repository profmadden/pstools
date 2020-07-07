//
//  pstool.c
//  FengShuiXX
//
//  Created by Patrick Madden on 5/17/20.
//  Copyright © 2020 Binghamton Optimality Research Group. All rights reserved.
//

#include "pstool.h"

int ps_init(FILE *fp, float originx, float originy, float width, float height)
{
    fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fp, "%%%%DocumentData: Clean7Bit\n");
    fprintf(fp, "%%%\%Origin: %10.2f %10.2f\n", originx, originy);
    fprintf(fp, "%%%%BoundingBox: %10.2f %10.2f %10.2f %10.2f\n", originx, originy, width, height);
    fprintf(fp, "%%%%LanguageLevel: 2\n");
    fprintf(fp, "%%%%Pages: 1\n");
    fprintf(fp, "%%%%Page: 1 1                           \n");
    
    fprintf(fp, "/Courier findfont 15 scalefont setfont\n");

    return 0;
}


int ps_setlinewidth(FILE *fp, float width)
{
    fprintf(fp, "%f setlinewidth\n",
            width);
    return 0;
}

int ps_setcolor(FILE *fp, float r, float g, float b)
{
    fprintf(fp, "%3.2f %3.2f %3.2f setrgbcolor\n",
            r, g, b);
    return 0;
}

int ps_setfont(FILE *fp, char *name, float fontsize)
{
    if (name == NULL)
        name = "Courier";
    
    fprintf(fp, "/%s findfont %f scalefont setfont\n", name, fontsize);
    return 0;
}
int ps_line(FILE *fp, float x1, float y1, float x2, float y2)
{
    fprintf(fp, "newpath %f %f moveto %f %f lineto stroke\n",
            x1, y1, x2, y2);
    return 0;
}

int ps_note(FILE *fp, char *note)
{
    fprintf(fp, "%% %s\n", note);
    return 0;
}

int ps_box(FILE *fp, float x1, float y1, float x2, float y2, int stroke, int fill)
{
    fprintf(fp, "newpath %f %f moveto ", x1, y1);
    fprintf(fp, "%f %f lineto ", x2, y1);
    fprintf(fp, "%f %f lineto ", x2, y2);
    fprintf(fp, "%f %f lineto ", x1, y2);
    fprintf(fp, "%f %f lineto ", x1, y1);
    if (fill)
    {
        if (stroke)
            fprintf(fp, "closepath gsave fill grestore stroke\n");
        else
            fprintf(fp, "closepath fill\n");
    }
    else
    {
        if (stroke)
            fprintf(fp, "closepath stroke\n");
    }
    return 0;
}

int ps_circle(FILE *fp, float cx, float cy, float radius, int stroke, int fill)
{
    fprintf(fp, "%f %f %f 0 360 arc closepath\n",
            cx, cy, radius);
    if (fill)
    {
        if (stroke)
            fprintf(fp, "gsave fill grestore stroke\n");
        else
            fprintf(fp, "fill\n");
    }
    else
    {
        if (stroke)
            fprintf(fp, "stroke\n");
    }
    return 0;
}

int ps_text(FILE *fp, float x, float y, char *text)
{
    fprintf(fp, "%f %f moveto (%s) show\n", x, y, text);
    return 0;
}

// Curved lines:
// newpath 20 20 moveto 60 60 lineto 100 150 110 320 180 400 curveto stroke

int ps_graphpoints(FILE *fp, int nv, float *x, float *y, float *z, int ne, int *v0, int *v1, float zscale)
{
    for (int e = 0; e < ne; ++e)
    {
        ps_line(fp, x[v0[e]], y[v0[e]], x[v1[e]], y[v1[e]]);
    }
    for (int v = 0; v < nv; ++v)
    {
        ps_circle(fp, x[v], y[v], 10, 1, 1);
    }
    
    return 0;
}

int ps_finish(FILE *fp)
{
    fprintf(fp, "%%%%EOF\n");
    return 0;
}
