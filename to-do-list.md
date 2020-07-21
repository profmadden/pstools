# PStools ToDo list

Let's build out some routines for PStools, that'll be handy in various
applications we're working on.

### Basic graphing container box with grid lines

Rectangular box, with origin, height, width.  Tick marks along the
sides for different units, with min and max values for the X and Y
axis.  Separate routine, so that we can overlay data on top of the
grids.

```
ps_graph_box(FILE *fp, float originx, float originy, float width, float height, float min_x, float max_x, float min_y, float max_y);
```

### Graph lines

Given two arrays of values, one for X, one for Y, and the origin
and size of a grid, and also

```
ps_graph_line(FILE *fp, float originx, float originy, float width, float height, int num_values, float *x, float *y);
```

### Pie Charts?

```
ps_pie_chart(FILE *fp, float originx, float originy, float width, float height,
int num_values, float *values, char **labels);
```

### 3D?

To handle 3d, will need to order the objects by the Z axis, and then render them one at a time, from "back" to "front".

Possibly something like

struct
{
float x1, y1, z1, x2, y2, z2;
int color_id;  // What color to draw
int stroke; // Should we stroke the outline
int fill;  // Color fill the rectangle?
struct ps_3d_object * next;
} ps_3d_object;

struct
{
ps_3d_object *list;
} ps_3d_space;

We create a "3d space" structure, and add items to it as a linked list.  Then, we call 3d_render, and it sorts the list from the back, and renders (creates the PostScript draw operation) in serial form.

int ps_3d_render(ps_3d_space *the3d_space);


