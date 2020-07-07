# pstools
A simple C wrapper library, for generating PostScript files.

[PostScript](https://www.adobe.com/content/dam/acom/en/devnet/actionscript/articles/PLRM.pdf)
is a handy language for creating graphics, text, and whatnot.
Really, some first-rate magic from the good folks at Adobe.  This
library is designed to make creating PostScript files from C programs
a little less cryptic, and a little less painful.

For writing raw PostScript, here's some good references:
* [PostScript Tutorial by Paul Bourke](http://paulbourke.net/dataformats/postscript/) - short, and gets right to the point.
* [Getting started in PostScript](https://www.math.ubc.ca/~cass/graphics/text/www/pdf/ch1.pdf) - more complex stuff
* [PostScript Tutorial and Cookbook](https://www-cdf.fnal.gov/offline/PostScript/BLUEBOOK.PDF) - the big guide


Open a file, and call **ps_init** to generate the boilerplate
PostScript, that should be at the front of a file.  This will create
a virtual drawing surface, with an XY origin, and a width and height.

```
int ps_init(FILE *fp, float originx, float originy, float width, float height);
```

Then, call the various **ps** routines with your C code, to create lines,
circles, text, and so on.  After you're done, call **ps_finish** and
close the file.

This should create a PostScript file that you can then view with Adobe
Acrobat, convert to encapsulated PostScript with gs, and so on.  We
use something like this:

```
gs -o OutputFileName.pdf -sDEVICE=pdfwrite -dEPSCrop InputFileName.ps
```

In our research group, we use this to generate debug information and
draw figures, from our design automation tools.  PostScript is cross-platform,
so there's no worries if we're running on Mac, Linux, or Windows.  The
PostScript renders nicely, is generally very compact, and makes it easy
to capture visuals at different points in the run of a tool.

