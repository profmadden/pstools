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

