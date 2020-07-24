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

typedef struct
{
  FILE *fp;
  // Entire drawing region for the PostScript file
  float origin_x, origin_y, width, height;
} ps_context;

typedef struct
{
  float min_x, min_y, max_x, max_y;
  float interval_x, interval_y;
} ps_frame;

typedef struct
{
	float min, max;
	int count, precision;
} ps_scale;

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
int ps_pie_chart(FILE* fp, float originx, float originy, float width, float height, int num_values, float* values, char** labels);
int ps_histogram(FILE* fp, float originx, float originy, float width, float height, char* x_label, char* y_label, ps_scale x_scale, ps_scale y_scale, float*bar_heights);

//3d stuff

typedef struct
{
	float x, y, z;
} ps_3d_vector;

typedef struct
{
	float r, g, b;
}  * ps_3d_color;

typedef struct ps_3d_object {
	ps_3d_vector pos,size;
	float z_rotation;
	ps_3d_color color;
	struct ps_3d_object* next;
} ps_3d_obj;

ps_3d_vector ps_3d_new_vector(float x, float y, float z);
ps_3d_vector ps_3d_add_vectors(ps_3d_vector first, ps_3d_vector second);
ps_3d_vector ps_3d_scale_vector(ps_3d_vector first, float scale);
ps_3d_color ps_3d_new_color(float r, float g, float b);
int ps_3d_draw_rectangle(FILE* fp, ps_3d_vector corners[4], ps_3d_color color);
int ps_3d_draw_cube(FILE* fp, ps_3d_vector pos, ps_3d_vector size, float z_rotation, ps_3d_color color);
int ps_3d_new_box(ps_3d_vector pos, ps_3d_vector size, float z_rotation, ps_3d_color color);
int ps_3d_draw_scene(FILE* fp, ps_3d_vector camera_pos);

#endif /* pstool_h */
