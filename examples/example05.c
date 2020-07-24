#include "../pstool.h"

int main()
{
	FILE* fp = fopen("example05.ps", "w");

	ps_init(fp, 0, 0, 3800, 2400);

	ps_3d_color color_palette[7] =
	{
		ps_3d_new_color(1, 0, 0),
		ps_3d_new_color(0, 1, 0),
		ps_3d_new_color(0, 0, 1),
		ps_3d_new_color(1, 1, 0),
		ps_3d_new_color(1, 0, 1),
		ps_3d_new_color(0, 1, 1),
		ps_3d_new_color(0, 0, 0)
	};
	
	ps_3d_color color= ps_3d_new_color(0.8, 0.2, 0.9);

	color = ps_3d_new_color(0.4, 0.2, 0.9);

	int i,j;
	for (i = 0; i < 7; i++)
		for (j = 0; j < 7; j++)
			ps_3d_new_box(ps_3d_new_vector(j*500+300, i*300-1500, 200), ps_3d_new_vector(400, 200, 50), 1,  color_palette[(i+j)%7]);
	
	ps_3d_draw_scene(fp,ps_3d_new_vector(2000,16000,-2000));

	ps_finish(fp);
	
	fclose(fp);
}