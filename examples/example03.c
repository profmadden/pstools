#include <stdio.h>
#include <math.h>
#include "../pstool.h"


#if 0

#endif

int main(int argc, char *argv[])
{
    ps_context * context = ps_init("example03.ps", 0, 0, 1000, 1000);
    // ps_graphpoints(fp, 5, x, y, z, 5, v0, v1, 0.0);
    
    struct graphexample boxgrid;
    boxgrid.originx = 700;
    boxgrid.originy = 650;
    boxgrid.width = 200;
    boxgrid.height = 200;
    boxgrid.intervalx = 10;
    boxgrid.intervaly = 10;
    
    struct graphexample g;
    g.originx = 400;
    g.originy = 400;
    g.width = 100;
    g.height = 100;
    g.intervalx = 5;
    g.intervaly = 10;
    
    struct graphminsmaxs range;
    range.min_x = 0;
    range.max_x = 40;
    range.min_y = 0;
    range.max_y = 30;
    
    ps_graph_box_grid(context, boxgrid, range);
   // ps_graph_box(fp, 700, 650, 200, 200, 0, 100, 0, 200, 10, 20);
    ps_graph_box(context, g, range);
    
    float x[5] = {0, 5, 15, 20, 40};
    float y[5] = {0, 10, 15, 25, 30};
    ps_graph_line(context, boxgrid, 5, x, y, range);
    ps_graph_line(context, g, 5, x, y, range);
    ps_finish(context);
    
    return 0;
}
