#include "../pstool.h"
#include <math.h>

int main()
{
	ps_context *context = ps_init("example06.ps", 0, 0, 550, 800);
	ps_setfont(context, "Courier", 14);

	ps_circ_zener_diode(context, 50, 200, 100, 250, 0);

	ps_circ_zener_diode(context, 150, 200, 200, 250, 1);

	ps_circ_transistor(context, 250, 200, 300, 250, 0);

	ps_circ_transistor(context, 350, 200, 400, 250, 1);

	ps_circ_capacitor(context, 450, 200, 500, 250, 0);

	ps_circ_capacitor(context, 50, 100, 100, 150, 1);

	//linear regulator

	ps_circ_transistor(context, 300, 600, 350, 650, 1);
	ps_circ_resistor(context, 200, 590, 210, 630);
	ps_circ_zener_diode(context, 310, 500, 340, 550, 1);
	ps_circ_capacitor(context, 100, 550, 150, 600, 1);
	ps_circ_capacitor(context, 400, 550, 450, 600, 1);
	
	//horizontal lines
	ps_line(context, 0, 650, 300, 650);
	ps_line(context, 350, 650, 800, 650);
	ps_line(context, 0, 450, 800, 450);

	//capacitors
	ps_line(context, 125, 600, 125, 650);
	ps_line(context, 125, 550, 125, 450);

	ps_line(context, 425, 600, 425, 650);
	ps_line(context, 425, 550, 425, 450);

	//resistance
	ps_line(context, 205, 630, 205, 650);
	ps_line(context, 205, 590, 205, 580);
	ps_line(context, 205, 580, 325, 580);

	//zener diode
	ps_line(context, 325, 550, 325, 600);
	ps_line(context, 325, 500, 325, 450);

	//labels
	ps_text(context, 10, 655, "+");
	ps_text(context, 10, 455, "gnd");

	ps_text(context, 500, 550, "load");

	ps_finish(context);
}
