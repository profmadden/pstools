demos:  example01.pdf

example01.pdf: example01
	./example01
	gs -o example01.pdf -sDEVICE=pdfwrite -dEPSCrop example01.ps

example01: example01.c ../pstool.c
	cc example01.c ../pstool.c -o example01



