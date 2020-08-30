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




struct graphexample
{
    float originx;
    float originy;
    float width;
    float height;
    float intervalx; //intervals are how far to space gridlines/ticks on each axis
    float intervaly;
};

struct graphminsmaxs
{
    float min_x;
    float max_x;
    float min_y;
    float max_y;
};

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


typedef struct
{
  FILE *fp;
  // Entire drawing region for the PostScript file
  float origin_x, origin_y, width, height;
} ps_context;


ps_context *ps_init(char *fn, float originx, float originy, float width, float height);
int ps_finish(ps_context *context);
int ps_setlinewidth(ps_context *context, float width);
int ps_setcolor(ps_context *context, float r, float g, float b);
int ps_setfont(ps_context *context, char *name, float fontsize);
int ps_line(ps_context *context, float x1, float y1, float x2, float y2);
int ps_note(ps_context *context, char *note);
int ps_box(ps_context *context, float x1, float y1, float x2, float y2, int stroke, int fill);
int ps_circle(ps_context *context, float cx, float cy, float radius, int stroke, int fill);
int ps_text(ps_context *context, float x, float y, char *text);
int ps_graphpoints(ps_context *context, int nv, float *x, float *y, float *z, int ne, int *v0, int *v1, float zscale);

int ps_pie_chart(ps_context *context, float originx, float originy, float width, float height, int num_values, float* values, char** labels);
int ps_histogram(ps_context *context, float originx, float originy, float width, float height, char* x_label, char* y_label, ps_scale x_scale, ps_scale y_scale, float*bar_heights);


int ps_graph_box(ps_context *context, struct graphexample graph, struct graphminsmaxs vals);

int ps_graph_box_grid(ps_context *context, struct graphexample graph, struct graphminsmaxs vals);

int ps_graph_line(ps_context *context, struct graphexample graph, int num_values, float *x, float *y, struct graphminsmaxs vals);
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

typedef enum { ps_3d_isometric, ps_3d_single_camera } ps_3d_perspective;

ps_3d_vector ps_3d_new_vector(float x, float y, float z);
ps_3d_vector ps_3d_add_vectors(ps_3d_vector first, ps_3d_vector second);
ps_3d_vector ps_3d_scale_vector(ps_3d_vector first, float scale);
ps_3d_color ps_3d_new_color(float r, float g, float b);
int ps_3d_new_box(ps_3d_vector pos, ps_3d_vector size, float z_rotation, ps_3d_color color);
int ps_3d_draw_scene(ps_context *context, ps_3d_vector camera_pos, ps_3d_perspective pers, ps_3d_vector angles);

//circuit stuff

int ps_circ_diode(ps_context *context, float x1, float y1, float x2, float y2, int isVertical);
int ps_circ_zener_diode(ps_context *context, float x1, float y1, float x2, float y2, int isVertical);
int ps_circ_resistor(ps_context *context, float x1, float y1, float x2, float y2);
int ps_circ_transistor(ps_context *context, float x1, float y1, float x2, float y2, int isVertical);
int ps_circ_capacitor(ps_context *context, float x1, float y1, float x2, float y2, int isVertical);

#endif /* pstool_h */
