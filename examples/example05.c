#include "../pstool.h"

int main()
{
	FILE* fp = fopen("example05.ps", "w");

	ps_init(fp, 0, 0, 1000, 1000);

	ps_3d_vector corners[4] = 
	{
		ps_3d_new_vector(200,200,0),
		ps_3d_new_vector(200,600,0),
		ps_3d_new_vector(600,200,0),
		ps_3d_new_vector(600,600,0),
	};

	ps_3d_draw_rectangle(fp,corners);

	ps_3d_new_box(
		ps_3d_new_vector(11, 11, 11),
		ps_3d_new_vector(11, 11, 11),
		0,
		ps_3d_new_color(55, 55, 55)
	);

	ps_finish(fp);

	fclose(fp);
}