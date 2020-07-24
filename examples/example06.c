#include "../pstool.h"

int main()
{
	FILE* fp = fopen("example06.ps", "w");

	ps_init(fp, 0, 0, 3800, 2400);

	ps_3d_color purple = ps_3d_new_color(0.4, 0.2, 0.9);
	ps_3d_color yellow = ps_3d_new_color(0.8, 0.8, 0);

	int i;
	for (i = 0; i < 5; i++)
	{
		ps_3d_new_box(ps_3d_new_vector(1000, 1200 + i * 600, 100), ps_3d_new_vector(5000, 300, 10), 0.01, purple);
	}
	ps_3d_new_box(ps_3d_new_vector(950, 1200, 110), ps_3d_new_vector(300, 2700, 10), 0.01, yellow);
	ps_3d_new_box(ps_3d_new_vector(5650, 1200, 110), ps_3d_new_vector(300, 2700, 10), 0.01, yellow);

	ps_3d_draw_scene(fp,ps_3d_new_vector(0,0,-150));

	ps_finish(fp);
	
	fclose(fp);
}