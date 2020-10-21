//
//  pstool.c
//  Simple library wrapper to generate PostScript files.
//
//  Created by Patrick Madden on 5/17/20.
//  Copyright © 2020 Binghamton Optimality Research Group. All rights reserved.
//

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "pstool.h"

float ps_fontsize;

ps_context *ps_init(char *fn, float originx, float originy, float width, float height)
{
    FILE *fp = fopen(fn, "w");
    if (fp == NULL)
        return NULL;
    
    ps_context *context = (ps_context *)malloc(sizeof(ps_context));
    if (context == NULL)
    {
        fclose(fp);
        return NULL;
    }
    
    context->fp = fp;
	fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fp, "%%%%DocumentData: Clean7Bit\n");
	fprintf(fp, "%%%\%Origin: %10.2f %10.2f\n", originx, originy);
	fprintf(fp, "%%%%BoundingBox: %10.2f %10.2f %10.2f %10.2f\n", originx, originy, width, height);
	fprintf(fp, "%%%%LanguageLevel: 2\n");
	fprintf(fp, "%%%%Pages: 1\n");
	fprintf(fp, "%%%%Page: 1 1                           \n");
    fprintf(fp, "%% Convert to PDF with something like this:\n");
    fprintf(fp, "%% gs -o OutputFileName.pdf -sDEVICE=pdfwrite -dEPSCrop InputFileName.ps\n");
    
	fprintf(fp, "/Courier findfont 15 scalefont setfont\n");
	ps_fontsize = 15;

	return context;
}


int ps_setlinewidth(ps_context *context, float width)
{
	fprintf(context->fp, "%f setlinewidth\n",
		width);
	return 0;
}

int ps_setcolor(ps_context *context, float r, float g, float b)
{
	fprintf(context->fp, "%3.2f %3.2f %3.2f setrgbcolor\n",
		r, g, b);
	return 0;
}

int ps_setfont(ps_context *context, char* name, float fontsize)
{
	if (name == NULL)
		name = "Courier";

	fprintf(context->fp, "/%s findfont %f scalefont setfont\n", name, fontsize);
	ps_fontsize = fontsize;
	return 0;
}

int ps_line(ps_context *context, float x1, float y1, float x2, float y2)
{
	fprintf(context->fp, "newpath %f %f moveto %f %f lineto stroke\n",
		x1, y1, x2, y2);
	return 0;
}

int ps_note(ps_context *context, char* note)
{
	fprintf(context->fp, "%% %s\n", note);
	return 0;
}

int ps_box(ps_context *context, float x1, float y1, float x2, float y2, int stroke, int fill)
{
	fprintf(context->fp, "newpath %f %f moveto ", x1, y1);
	fprintf(context->fp, "%f %f lineto ", x2, y1);
	fprintf(context->fp, "%f %f lineto ", x2, y2);
	fprintf(context->fp, "%f %f lineto ", x1, y2);
	fprintf(context->fp, "%f %f lineto ", x1, y1);
	if (fill)
	{
		if (stroke)
			fprintf(context->fp, "closepath gsave fill grestore stroke\n");
		else
			fprintf(context->fp, "closepath fill\n");
	}
	else
	{
		if (stroke)
			fprintf(context->fp, "closepath stroke\n");
	}
	return 0;
}

int ps_circle(ps_context *context, float cx, float cy, float radius, int stroke, int fill)
{
	fprintf(context->fp, "%f %f %f 0 360 arc closepath\n",
		cx, cy, radius);
	if (fill)
	{
		if (stroke)
			fprintf(context->fp, "gsave fill grestore stroke\n");
		else
			fprintf(context->fp, "fill\n");
	}
	else
	{
		if (stroke)
			fprintf(context->fp, "stroke\n");
	}
	return 0;
}

int ps_text(ps_context *context, float x, float y, char* text)
{
	fprintf(context->fp, "%f %f moveto (%s) show\n", x, y, text);
	return 0;
}

// Curved lines:
// newpath 20 20 moveto 60 60 lineto 100 150 110 320 180 400 curveto stroke

int ps_graphpoints(ps_context *context, int nv, float* x, float* y, float* z, int ne, int* v0, int* v1, float zscale)
{
	for (int e = 0; e < ne; ++e)
	{
		ps_line(context, x[v0[e]], y[v0[e]], x[v1[e]], y[v1[e]]);
	}
	for (int v = 0; v < nv; ++v)
	{
		ps_circle(context, x[v], y[v], 10, 1, 1);
	}

	return 0;
}


int ps_graph_box(ps_context *context, struct graphexample graph, struct graphminsmaxs values)
{

	float scalex = graph.width / values.max_x;
	float scaley = graph.height / values.max_y;

	ps_line(context, graph.originx, graph.originy, graph.originx + graph.width, graph.originy);
	ps_line(context, graph.originx, graph.originy, graph.originx, graph.originy + graph.height);

	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx, graph.originy - 12, values.min_x);
	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy, values.min_y);

	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx + graph.width, graph.originy - 12, values.max_x);
	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy + graph.height, values.max_y);

	//draws vertical tick lines
	for (int i = graph.originx; i <= graph.originx + graph.width; i += (graph.intervalx * scalex))
	{
		ps_line(context, i, graph.originy - 2, i, graph.originy);
	}

	//draws horizontal tick lines
	for (int i = graph.originy; i <= graph.originy + graph.height; i += (graph.intervaly * scaley))
	{
		ps_line(context, graph.originx - 2, i, graph.originx, i);
	}

	return 0;
}

int ps_graph_box_grid(ps_context *context, struct graphexample graph, struct graphminsmaxs values)
{

	float scalex = graph.width / values.max_x;
	float scaley = graph.height / values.max_y;

	ps_line(context, graph.originx, graph.originy, graph.originx + graph.width, graph.originy);
	ps_line(context, graph.originx, graph.originy, graph.originx, graph.originy + graph.height);

	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx, graph.originy - 12, values.min_x);
	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy, values.min_y);

	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx + graph.width, graph.originy - 12, values.max_x);
	fprintf(context->fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy + graph.height, values.max_y);

	//draws vertical grid lines
	for (int i = graph.originx; i <= graph.originx + graph.width; i += (graph.intervalx * scalex))
	{
		ps_line(context, i, graph.originy - 2, i, graph.originy + graph.height);
	}

	//draws horizontal grid lines
	for (int i = graph.originy; i <= graph.originy + graph.height; i += (graph.intervaly * scaley))
	{
		ps_line(context, graph.originx - 2, i, graph.originx + graph.width, i);
	}

	return 0;
}

int ps_graph_line(ps_context *context, struct graphexample graph, int num_values, float* x, float* y, struct graphminsmaxs values)
{
	float scalex = graph.width / values.max_x;
	float scaley = graph.height / values.max_y;
	for (int i = 0; i < num_values; i++)
	{
		ps_circle(context, graph.originx + (x[i] * scalex), graph.originy + (y[i] * scaley), 2, 1, 1);
		if (i < num_values - 1) {
			ps_line(context, graph.originx + (x[i] * scalex), graph.originy + (y[i] * scaley), graph.originx + (x[i + 1] * scalex), graph.originy + (y[i + 1] * scaley));
		}
	}

	return 0;
}

int ps_pie_chart(ps_context *context, float originx, float originy, float width, float height, int num_values, float* values, char** labels)
{
	float radius = width / 2;
	ps_circle(context, originx, originy, radius, 1, 0);
	int i;
	float targetx, targety, angle = 0;
	for (i = 0; i < num_values; i++) //for lines
	{
		targetx = originx + cos(angle) * radius;
		targety = originy + sin(angle) * radius;
		ps_line(context, originx, originy, targetx, targety);
		angle += 2.0F * M_PI * values[i];
	}
	angle = 0;
	for (i = 0; i < num_values; i++) //for labels
	{
		angle += M_PI * (values[i] + (i > 0 ? values[i - 1] : 0.0F));
		targetx = originx + cos(angle) * radius;
		targety = originy + sin(angle) * radius;
		ps_text(context,
			(targetx * 2 + originx) / 3 - ((ps_fontsize/3) * strlen(labels[i])),
			(targety * 2 + originy) / 3 - (ps_fontsize / 3),
			labels[i]);
	}
	return 0;
}


int ps_histogram(ps_context *context, float originx, float originy, float width, float height, char* x_label, char* y_label, ps_scale x_scale, ps_scale y_scale, float* bar_heights)
{
	ps_line(context, originx,originy, originx + width,originy); //initial lines and labels
	ps_line(context, originx,originy,originx, originy + height);
	ps_text(context, originx + width, originy, x_label);
	ps_text(context, originx, originy+height, y_label);

	int i;
	float value_scale = (x_scale.max - x_scale.min) / x_scale.count;
	float scale = width / x_scale.count;
	char label_buffer_x[x_scale.precision+1];

	for (i = 0; i < x_scale.count+1; i++) //x axis values
	{
		snprintf(label_buffer_x, sizeof(label_buffer_x), "%f", x_scale.min + value_scale * i);
		ps_text(context, originx + scale * i, originy - ps_fontsize , label_buffer_x);
		if (i < x_scale.count)
			ps_box(context,
				originx + (scale * i),
				originy,
				originx + (scale * (i+1)),
				originy+height*((bar_heights[i]-y_scale.min)/(y_scale.max-y_scale.min)),
				1,
				i%2);
	}

	value_scale = (y_scale.max - y_scale.min) / y_scale.count;
	scale = height / y_scale.count;
	char label_buffer_y[y_scale.precision + 1];

	for (i = 0; i < y_scale.count+1; i++) //y axis values
	{
		snprintf(label_buffer_y, sizeof(label_buffer_y), "%f", y_scale.min + value_scale * i);
		ps_text(context, originx - (ps_fontsize * (((float)sizeof(label_buffer_y))/2)) , originy + scale * i,  label_buffer_y);
	}

	return 0;
}

int ps_finish(ps_context *context)
{
	fprintf(context->fp, "%%%%EOF\n");
    fclose(context->fp);
    
    free(context);

	return 0;
}
