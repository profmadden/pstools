//
//  example.c
//  A small example for using the PStools code
//
//  Created by Patrick Madden on 7/3/20.
//  Copyright © 2020 Binghamton Optimality Research Group. All rights reserved.
//
// To convert postscript to PDF, keeping bounding box intact:
// gs -o pstest.pdf -sDEVICE=pdfwrite -dEPSCrop pstest.ps

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../pstool.h"

float x[] = {0, 33, 404, 571, 18};
float y[] = {200, 93, 59, 843, 197};
float z[] = {300, 143, 804, 271, 438};

int v0[] = {0, 1, 2, 3, 4};
int v1[] = {3, 2, 1, 4, 3};


void ps_solspace(int n, int bits, float llx, float lly, float urx, float ury,
		 float *x, float *y)
{
  float dx = urx - llx;
  float dy = ury - lly;
  
  if (bits > 2)
    {
      int quad = n & 0x3;
      n = n >> 2;
      switch (quad)
	{
	case 0:
	  ps_solspace(n, bits - 1, llx, lly, llx + dx/2, lly + dy/2, x, y);
	  break;
	case 1:
	  ps_solspace(n, bits - 1, llx + dx/2, lly, urx, lly + dy/2, x, y);
	  break;
	case 2:
	  ps_solspace(n, bits - 1, llx, lly + dy/2, llx + dx/2, ury, x, y);
	  break;
	case 3:
	  ps_solspace(n, bits - 1, llx + dx/2, lly + dy/2, urx, ury, x, y);
	  break;
      }
    }
  else
    {
      int quad = n & 0x3;
      switch (quad)
        {
        case 0:
	  *x = llx + dx/4;
	  *y = lly + dy/4;
          break;
        case 1:
	  *x = llx + dx/4;
	  *y = ury - dy/4;
          break;
	case 2:
	  *x = urx - dx/4;
	  *y = lly + dy/4;
          break;
        case 3:
	  *x = urx - dx/4;
	  *y = ury - dy/4;
          break;
	}
    }
}

float perp_point(float x0, float y0, float x1, float y1, float bend, float *x, float *y)
{
  float dx = x1 - x0;
  float dy = y1 - y0;
  // Unit deltas for perpendicular line
  float perpx, perpy;

  if (dx == 0)
    {
      perpx = 1;
      perpy = 0;
    }
  else
    {
      perpx = dy/dx;
      perpy = 1;
      float length = sqrt(perpx * perpx + perpy * perpy);
      perpx = perpx / length;
      perpy = perpy / length;
    }

  *x = ((x0 + x1)/2) + bend * perpx;
  *y = ((y0 + y1)/2) + bend * perpy;

#if 0
  printf("Line %f %f to %f %f    point %f %f\n",
	 x0, y0, x1, y1, *x, *y);
#endif

  return 0;
}


int main(int argc, char *argv[])
{
  float x, y;
  int bits = 8;

  if (argc == 2)
    {
      bits = atoi(argv[1]);
    }

  perp_point(0, 0, 100, 0, 5, &x, &y);
  perp_point(0, 100, 0, 0, 5, &x, &y);

  perp_point(0, 0, 100, 100, 5, &x, &y);


    FILE *fp = fopen("example02.ps", "w");
    
    ps_init(fp, 0, 0, 1000, 1000);



    //float x, y;
    for (int i = 0; i < (1 << bits); ++i)
      {
	for (int b = 0; b < bits; ++b)
	  {
	    if (i & (1 << b))
	      {
		int j = i & ~(1 << b);
		float x0, y0, x1, y1, midx, midy;
		ps_solspace(i, bits, 100, 100, 900, 900, &x0, &y0);
		ps_solspace(j, bits, 100, 100, 900, 900, &x1, &y1);
		perp_point(x0, y0, x1, y1, 80, &midx, &midy);
		//ps_line(fp, x0 + i, y0 + i, x1 + j, y1 + j);
		fprintf(fp, "%f %f moveto %f %f %f %f %f %f curveto stroke\n",
		       x0, y0, x0, y0, midx, midy, x1, y1);
	      }
	  }
      }


    for (int i = 0; i < (1 << bits); ++i)
      {
	ps_solspace(i, bits, 100, 100, 900, 900, &x, &y);
	ps_circle(fp, x, y, 3, 0, 1);
      }


    ps_finish(fp);
    
    fclose(fp);

    return 0;
}
