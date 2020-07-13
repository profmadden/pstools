demos:  example01.pdf

example01.pdf: example01
	./example01
	gs -o example01.pdf -sDEVICE=pdfwrite -dEPSCrop example01.ps

example01: example01.c ../pstool.c
	cc example01.c ../pstool.c -o example01 -lm

piechartexample.pdf: piechartexample
	./piechartexample
	gs -o piechartexample.pdf -sDEVICE=pdfwrite -dEPSCrop piechartexample.ps

piechartexample: piechartexample.c ../pstool.c
	cc piechartexample.c ../pstool.c -o piechartexample -lm



