#include "../pstool.h"

int main()
{
	ps_context *context = ps_init("example04.ps", 0, 0, 1000, 1000);

	char* labels[5];
	labels[0] = "cat";
	labels[1] = "dog";
	labels[2] = "rabbit";
	labels[3] = "turtle";
	labels[4] = "sheep";

	float values[5] = { 0.50F,0.25F,0.15F,0.08F,0.02F };

	ps_pie_chart(context, 200, 800, 300, 300, 5, values, labels);

	ps_setfont(context, "Courier", 10);

	float bar_heights[10] = { 10,20,30,40,50,50,40,30,20,10 };

	ps_scale x_scale = { .min = 0,.max = 100,.count = 10 ,.precision=5};
	ps_scale y_scale = { .min = 0,.max = 50,.count = 10 ,.precision=5};

	ps_histogram(context, 500, 650, 400, 300, "x_label", "y_label", x_scale, y_scale, bar_heights);

	y_scale.min = 20;
	y_scale.max = 55.6;
	y_scale.precision = 7;
	ps_histogram(context, 500, 250, 400, 300, "x_label", "y_label", x_scale, y_scale, bar_heights);

    ps_setfont(context, "Courier", 7);

	y_scale.min = -20;
	y_scale.max = 120;
	ps_histogram(context, 50, 250, 300, 400, "x_label", "y_label", x_scale, y_scale, bar_heights);

	ps_finish(context);
}
