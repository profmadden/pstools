#include "pstool.h"

int ps_circ_diode(ps_context *context, float x1, float y1, float x2, float y2, int isVertical)
{
	if (isVertical)
	{
		ps_line(context, x1, y1, x2, y1);
		ps_line(context, x1, y1, (x1 + x2) / 2, y2);
		ps_line(context, x2, y1, (x1 + x2) / 2, y2);
		ps_line(context, x1, y2, x2, y2);
	}
	else
	{
		ps_line(context, x1, y1, x1, y2);
		ps_line(context, x1, y1, x2, (y1 + y2) / 2);
		ps_line(context, x1, y2, x2, (y1 + y2) / 2);
		ps_line(context, x2, y1, x2, y2);
	}
	return 0;
}

int ps_circ_zener_diode(ps_context *context, float x1, float y1, float x2, float y2, int isVertical)
{
	ps_circ_diode(context, x1, y1, x2, y2, isVertical);
	if (isVertical)
	{
		ps_line(context, x2, y2, x2, y2 + ((y2 - y1) / 4));
		ps_line(context, x1, y2, x1, y2 - ((y2 - y1) / 4));
	}
	else
	{
		ps_line(context, x2, y2, x2 + ((x2 - x1) / 4), y2);
		ps_line(context, x2, y1, x2 - ((x2 - x1) / 4), y1);
	}
	return 0;
}

int ps_circ_resistor(ps_context *context, float x1, float y1, float x2, float y2)
{
	ps_box(context, x1, y1, x2, y2,1,0);
	return 0;
}

int ps_circ_transistor(ps_context *context, float x1, float y1, float x2, float y2, int isVertical)
{
	if (isVertical)
	{
		ps_line(context,(x1+x2)/2,y1,(x1+x2)/2,(y1 * 2 + y2) /3);//base trace
		ps_line(context, (3 * x1 + x2) / 4, (2 * y1 + y2) / 3,  (x1 + 3 * x2) / 4,(2 * y1 + y2) / 3); //transistor itself
		//collector and emitter
		ps_line(context,  (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, x1, y2);
		ps_line(context, (x1 + 2 * x2) / 3, (2 * y1 + y2) / 3, x2, y2);
		//circle
		ps_circle(context, (x1 + x2) / 2, (y1 + y2) / 2 + (y2 - y1) / 5, (y1 - y2) / 2, 1, 0);
	}
	else
	{
		ps_line(context, x1, (y1 + y2) / 2, (2*x1 + x2) / 3, (y1 + y2) / 2); //base trace
		ps_line(context, (2 * x1 + x2) / 3, (3 * y1 + y2) / 4, (2 * x1 + x2) / 3, (y1 + 3 * y2) / 4); //transistor itself
		//collector and emitter
		ps_line(context, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, x2, y1);
		ps_line(context, (2 * x1 + x2) / 3, ( y1 + 2 * y2) / 3, x2, y2);
		//circle
		ps_circle(context, (x1 + x2) / 2 + (x2 - x1) / 5, (y1 + y2) / 2, (y1 - y2) / 2, 1, 0);
	}
	return 0;
}


int ps_circ_capacitor(ps_context *context, float x1, float y1, float x2, float y2, int isVertical)
{
	if (isVertical)
	{
		ps_line(context,  (x1 + x2) / 2, y1, (x1 + x2) / 2, (y1 * 2 + y2) / 3);
		ps_line(context,  (x1 + x2) / 2, y2, (x1 + x2) / 2,(y1 + y2 * 2) / 3);

		ps_line(context,  x1,(y1 * 2 + y2) / 3, x2, (y1 * 2 + y2) / 3);
		ps_line(context, x1, (y1 + y2 * 2) / 3, x2, (y1 + y2 * 2) / 3);
	}
	else
	{
		ps_line(context, x1, (y1 + y2) / 2, (x1 * 2+ x2 ) / 3, (y1 + y2) / 2);
		ps_line(context, x2, (y1 + y2) / 2, (x1 + x2 * 2) / 3, (y1 + y2) / 2);

		ps_line(context, (x1 * 2 + x2) / 3, y1, (x1 * 2 + x2) / 3, y2);
		ps_line(context, (x1 + x2 * 2) / 3, y1, (x1  + x2* 2) / 3, y2);
	}
	return 0;
}
