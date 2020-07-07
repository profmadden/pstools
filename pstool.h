//
//  pstool.h
//  FengShuiXX
//
//  Created by Patrick Madden on 5/17/20.
//  Copyright © 2020 Binghamton Optimality Research Group. All rights reserved.
//

#ifndef pstool_h
#define pstool_h

#include <stdio.h>
int ps_init(FILE *fp, float originx, float originy, float width, float height);
int ps_setlinewidth(FILE *fp, float width);
int ps_setcolor(FILE *fp, float r, float g, float b);
int ps_setfont(FILE *fp, char *name, float fontsize);
int ps_line(FILE *fp, float x1, float y1, float x2, float y2);
int ps_note(FILE *fp, char *note);
int ps_box(FILE *fp, float x1, float y1, float x2, float y2, int stroke, int fill);
int ps_circle(FILE *fp, float cx, float cy, float radius, int stroke, int fill);
int ps_text(FILE *fp, float x, float y, char *text);
int ps_graphpoints(FILE *fp, int nv, float *x, float *y, float *z, int ne, int *v0, int *v1, float zscale);
int ps_finish(FILE *fp);

#endif /* pstool_h */
