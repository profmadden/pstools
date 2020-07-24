#include "../pstool.h"

int main()
{
	FILE* fp = fopen("example05.ps", "w");

	ps_init(fp, 0, 0, 1000, 1000);

	ps_3d_color color= ps_3d_new_color(0.8, 0.2, 0.9);

	color = ps_3d_new_color(0.4, 0.2, 0.9);

	ps_3d_draw_cube(fp, ps_3d_new_vector(400, 400, 200), ps_3d_new_vector(200, 200, 200),0, color);

	ps_finish(fp);
	
	fclose(fp);
}