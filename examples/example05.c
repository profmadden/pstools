#include "../pstool.h"

int main()
{
	FILE* fp = fopen("example05.ps", "w");

	ps_init(fp, 0, 0, 2000, 2000);

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

	int i;
	for (i=0;i<7;i++)
		ps_3d_new_box(ps_3d_new_vector(400, i*100, 200), ps_3d_new_vector(800, 200, 400), i/3.1415, color_palette[i]);
	
	ps_3d_draw_scene(fp,ps_3d_new_vector(2000,4000,-2000));

	ps_finish(fp);
	
	fclose(fp);
}