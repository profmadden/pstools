#include "../pstool.h"
#include <math.h>

int main()
{
	ps_context *context = ps_init("example05.ps", 0, 0, 3000, 2000);
	ps_setfont(context, "Courier", 30);

	ps_3d_color blue = ps_3d_new_color(0.2, 0.2, 0.9);
	ps_3d_color green = ps_3d_new_color(0, 0.6, 0);
	ps_3d_color grey = ps_3d_new_color(0.2, 0.2, 0.2);
	ps_3d_color orange = ps_3d_new_color(1, 0.3, 0);

	ps_3d_new_box(ps_3d_new_vector(400, 500, 0), ps_3d_new_vector(200, 20, 210), 0, orange);
	ps_3d_new_box(ps_3d_new_vector(650, 500, 0), ps_3d_new_vector(200, 20, 210), 0, orange);

	ps_3d_new_box(ps_3d_new_vector(400, 530, 0), ps_3d_new_vector(450, 20, 30), 0, blue);
	ps_3d_new_box(ps_3d_new_vector(400, 530, 60), ps_3d_new_vector(450, 20, 30), 0, blue);
	ps_3d_new_box(ps_3d_new_vector(400, 530, 120), ps_3d_new_vector(450, 20, 30), 0, blue);
	ps_3d_new_box(ps_3d_new_vector(400, 530, 180), ps_3d_new_vector(450, 20, 30), 0, blue);

	ps_3d_draw_scene(context, ps_3d_new_vector(2500, 2800, -1000), ps_3d_single_camera, ps_3d_new_vector(0, 0, 0));


	ps_text(context, 400, 450, "single camera perspective");

	ps_3d_new_box(ps_3d_new_vector(1200, 500, 0), ps_3d_new_vector(200, 20, 210), 0, orange);
	ps_3d_new_box(ps_3d_new_vector(1450, 500, 0), ps_3d_new_vector(200, 20, 210), 0, orange);

	ps_3d_new_box(ps_3d_new_vector(1200, 530, 0), ps_3d_new_vector(450, 20, 30), 0, blue);
	ps_3d_new_box(ps_3d_new_vector(1200, 530, 60), ps_3d_new_vector(450, 20, 30), 0, blue);
	ps_3d_new_box(ps_3d_new_vector(1200, 530, 120), ps_3d_new_vector(450, 20, 30), 0, blue);
	ps_3d_new_box(ps_3d_new_vector(1200, 530, 180), ps_3d_new_vector(450, 20, 30), 0, blue);

	ps_3d_draw_scene(context, ps_3d_new_vector(0, 0, 0), ps_3d_isometric, ps_3d_new_vector(M_PI / 4, M_PI/3, 0));
	ps_text(context, 1200, 450, "isometric perspective");

	ps_finish(context);

}
