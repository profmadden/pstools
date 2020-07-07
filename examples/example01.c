//
//  example.c
//  A small example for using the PStools code
//
//  Created by Patrick Madden on 7/3/20.
//  Copyright © 2020 Binghamton Optimality Research Group. All rights reserved.
//
// To convert postscript to PDF, keeping bounding box intact:
// gs -o pstest.pdf -sDEVICE=pdfwrite -dEPSCrop pstest.ps

#include <stdio.h>
#include <math.h>
#include "../pstool.h"

float x[] = {0, 33, 404, 571, 18};
float y[] = {200, 93, 59, 843, 197};
float z[] = {300, 143, 804, 271, 438};

int v0[] = {0, 1, 2, 3, 4};
int v1[] = {3, 2, 1, 4, 3};


int ps_solspace(FILE *fp, int n, int llx, int lly, int width, int bend)
{
    int bits = ((int)log2(n)) + 1;
    float vi[2], vj[2];

    //printf("Value %d requires %d bits\n", n, bits);
    int edgecount = 0;


    for (int i = 0; i < n; ++i)
    {
        vi[0] = llx + (((float)i / n) * width);
        vi[1] = lly;
        
        for (int b = 0; b < bits; ++b)
        {
            if (i & (1 << b))
            {
                int j = i & ~(1 << b);
                //printf("Number %d bit %d  - back to %d\n", i, b, j);
                ++edgecount;

                vj[0] = llx + (((float)j / n) * width);
                vj[1] = lly;
                
                int dist = j - i;
                
                fprintf(fp, "%f %f moveto %f %f %f %f %f %f curveto stroke\n",
                        vi[0], vi[1],
                        vi[0], vi[1],
                        (vi[0] + vj[0])/2, vi[1] + bend*dist,
                        vj[0], vj[1]);
            }
        }

    }
    for (int i = 0; i < n; ++i)
    {
        float x = llx + (((float) i/n) * width);
        float y = lly;
        ps_circle(fp, x, y, bend/6.0, 0, 1);
    }
    
    //printf("%d edges\n", edgecount);
    return 0;
}


void ps_tree_pos(int llx, int lly, int width, int height,
                  int level,
                  int levels,
                  int branch, float *x, float *y)
{
    // Spacing -- if we are on level 0, then we split
    // at halfway.  Otherwise, we add one, so that the
    // vertices are better distributed
    if (level == 0)
    {
        *x = llx + width / 2.0;
    }
    else
    {
        if (level != levels)
            *x = llx + ((float) branch + 1) * (width / ((1 << level) + 1.0));
        else
            *x = llx + branch * ((float)width / (1 << level));
    }

    *y = lly + (float)level/levels * height;
}

int ps_soltree(FILE *fp, int n, int llx, int lly, int width, int height)
{
    int branches = 2;
    int levels = ((int)log2(n));
    
    int level = 1;

    while (branches <= n)
    {
        float x1, y1, x2, y2;

        for (int b = 0; b < branches; ++b)
        {
            ps_tree_pos(llx, lly, width, height, level - 1, levels,
                        b/2, &x1, &y1);
            ps_tree_pos(llx, lly, width, height, level, levels,
                        b, &x2, &y2);
            
            ps_line(fp, x1, y1, x2, y2);
        }
        ++level;
        branches = branches * 2;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    FILE *fp = fopen("example01.ps", "w");
    
    ps_init(fp, 0, 0, 1000, 1000);
    // ps_graphpoints(fp, 5, x, y, z, 5, v0, v1, 0.0);
    
    ps_soltree( fp, 32, 50, 900, 900, -600);
    ps_solspace(fp, 32, 50, 300, 900, 25);

    ps_finish(fp);
    
    fclose(fp);

    return 0;
}
