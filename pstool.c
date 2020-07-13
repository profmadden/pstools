//
//  pstool.c
//  FengShuiXX
//
//  Created by Patrick Madden on 5/17/20.
//  Copyright © 2020 Binghamton Optimality Research Group. All rights reserved.
//

#include <math.h>
#include "pstool.h"

#define pi 3.14159265358979323846

int ps_init(FILE* fp, float originx, float originy, float width, float height)
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


int ps_setlinewidth(FILE* fp, float width)
{
	fprintf(fp, "%f setlinewidth\n",
		width);
	return 0;
}

int ps_setcolor(FILE* fp, float r, float g, float b)
{
	fprintf(fp, "%3.2f %3.2f %3.2f setrgbcolor\n",
		r, g, b);
	return 0;
}

int ps_setfont(FILE* fp, char* name, float fontsize)
{
	if (name == NULL)
		name = "Courier";

	fprintf(fp, "/%s findfont %f scalefont setfont\n", name, fontsize);
	return 0;
}

int ps_line(FILE* fp, float x1, float y1, float x2, float y2)
{
	fprintf(fp, "newpath %f %f moveto %f %f lineto stroke\n",
		x1, y1, x2, y2);
	return 0;
}

int ps_note(FILE* fp, char* note)
{
	fprintf(fp, "%% %s\n", note);
	return 0;
}

int ps_box(FILE* fp, float x1, float y1, float x2, float y2, int stroke, int fill)
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

int ps_circle(FILE* fp, float cx, float cy, float radius, int stroke, int fill)
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

int ps_text(FILE* fp, float x, float y, char* text)
{
	fprintf(fp, "%f %f moveto (%s) show\n", x, y, text);
	return 0;
}

// Curved lines:
// newpath 20 20 moveto 60 60 lineto 100 150 110 320 180 400 curveto stroke

int ps_graphpoints(FILE* fp, int nv, float* x, float* y, float* z, int ne, int* v0, int* v1, float zscale)
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

struct graphexample
{
	float originx;
	float originy;
	float width;
	float height;
	float intervalx; //intervals are how far to space gridlines/ticks on each axis
	float intervaly;
};

//values of min and max x and y's -- helpful for determining scale on graph for grid lines and plotting points accurately 6 
struct graphminsmaxs
{
	float min_x;
	float max_x;
	float min_y;
	float max_y;
};

int ps_graph_box(FILE* fp, struct graphexample graph, struct graphminsmaxs values)
{

	float scalex = graph.width / values.max_x;
	float scaley = graph.height / values.max_y;

	ps_line(fp, graph.originx, graph.originy, graph.originx + graph.width, graph.originy);
	ps_line(fp, graph.originx, graph.originy, graph.originx, graph.originy + graph.height);

	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx, graph.originy - 12, values.min_x);
	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy, values.min_y);

	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx + graph.width, graph.originy - 12, values.max_x);
	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy + graph.height, values.max_y);

	//draws vertical tick lines
	for (int i = graph.originx; i <= graph.originx + graph.width; i += (graph.intervalx * scalex))
	{
		ps_line(fp, i, graph.originy - 2, i, graph.originy);
	}

	//draws horizontal tick lines
	for (int i = graph.originy; i <= graph.originy + graph.height; i += (graph.intervaly * scaley))
	{
		ps_line(fp, graph.originx - 2, i, graph.originx, i);
	}

	return 0;
}

int ps_graph_box_grid(FILE* fp, struct graphexample graph, struct graphminsmaxs values)
{

	float scalex = graph.width / values.max_x;
	float scaley = graph.height / values.max_y;

	ps_line(fp, graph.originx, graph.originy, graph.originx + graph.width, graph.originy);
	ps_line(fp, graph.originx, graph.originy, graph.originx, graph.originy + graph.height);

	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx, graph.originy - 12, values.min_x);
	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy, values.min_y);

	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx + graph.width, graph.originy - 12, values.max_x);
	fprintf(fp, "%f %f moveto (%.1f) show\n", graph.originx - 35, graph.originy + graph.height, values.max_y);

	//draws vertical grid lines
	for (int i = graph.originx; i <= graph.originx + graph.width; i += (graph.intervalx * scalex))
	{
		ps_line(fp, i, graph.originy - 2, i, graph.originy + graph.height);
	}

	//draws horizontal grid lines
	for (int i = graph.originy; i <= graph.originy + graph.height; i += (graph.intervaly * scaley))
	{
		ps_line(fp, graph.originx - 2, i, graph.originx + graph.width, i);
	}

	return 0;
}

int ps_graph_line(FILE* fp, struct graphexample graph, int num_values, float* x, float* y, struct graphminsmaxs values)
{
	float scalex = graph.width / values.max_x;
	float scaley = graph.height / values.max_y;
	for (int i = 0; i < num_values; i++)
	{
		ps_circle(fp, graph.originx + (x[i] * scalex), graph.originy + (y[i] * scaley), 2, 1, 1);
		if (i < num_values - 1) {
			ps_line(fp, graph.originx + (x[i] * scalex), graph.originy + (y[i] * scaley), graph.originx + (x[i + 1] * scalex), graph.originy + (y[i + 1] * scaley));
		}
	}

	return 0;
}

int ps_pie_chart(FILE* fp, float originx, float originy, float width, float height, int num_values, float* values, char** labels)
{
	float radius = width / 2;
	ps_circle(fp, originx, originy, radius, 1, 0);
	int i;
	float targetx, targety, angle = 0;
	for (i = 0; i < num_values; i++) //for lines
	{
		targetx = originx + cos(angle) * radius;
		targety = originy + sin(angle) * radius;
		ps_line(fp, originx, originy, targetx, targety);
		angle += 2.0F * pi * values[i];
	}
	angle = 0;
	for (i = 0; i < num_values; i++) //for labels
	{
		angle += pi * (values[i] + (i > 0 ? values[i - 1] : 0.0F));
		targetx = originx + cos(angle) * radius;
		targety = originy + sin(angle) * radius;
		ps_text(fp, (targetx * 2 + originx) / 3, (targety * 2 + originy) / 3, labels[i]);
	}
	return 0;
}

int ps_finish(FILE* fp)
{
	fprintf(fp, "%%%%EOF\n");
	return 0;
}
