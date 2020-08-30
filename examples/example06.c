#include "../pstool.h"
#include <math.h>

int main()
{
	FILE* fp = fopen("example06.ps", "w");

	ps_init(fp, 0, 0, 550, 800);
	ps_setfont(fp, "Courier", 14);

	ps_circ_zener_diode(fp, 50, 200, 100, 250, 0);

	ps_circ_zener_diode(fp, 150, 200, 200, 250, 1);

	ps_circ_transistor(fp, 250, 200, 300, 250, 0);

	ps_circ_transistor(fp, 350, 200, 400, 250, 1);

	ps_circ_capacitor(fp, 450, 200, 500, 250, 0);

	ps_circ_capacitor(fp, 50, 100, 100, 150, 1);

	//linear regulator

	ps_circ_transistor(fp, 300, 600, 350, 650, 1);
	ps_circ_resistor(fp, 200, 590, 210, 630);
	ps_circ_zener_diode(fp, 310, 500, 340, 550, 1);
	ps_circ_capacitor(fp, 100, 550, 150, 600, 1);
	ps_circ_capacitor(fp, 400, 550, 450, 600, 1);
	
	//horizontal lines
	ps_line(fp, 0, 650, 300, 650);
	ps_line(fp, 350, 650, 800, 650);
	ps_line(fp, 0, 450, 800, 450);

	//capacitors
	ps_line(fp, 125, 600, 125, 650);
	ps_line(fp, 125, 550, 125, 450);

	ps_line(fp, 425, 600, 425, 650);
	ps_line(fp, 425, 550, 425, 450);

	//resistance
	ps_line(fp, 205, 630, 205, 650);
	ps_line(fp, 205, 590, 205, 580);
	ps_line(fp, 205, 580, 325, 580);

	//zener diode
	ps_line(fp, 325, 550, 325, 600);
	ps_line(fp, 325, 500, 325, 450);

	//labels
	ps_text(fp, 10, 655, "+");
	ps_text(fp, 10, 455, "gnd");

	ps_text(fp, 500, 550, "load");

	ps_finish(fp);

	fclose(fp);
}