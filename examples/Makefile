demos:  example01.pdf example02.pdf example03.pdf

example01.pdf: example01
	./example01
	gs -o example01.pdf -sDEVICE=pdfwrite -dEPSCrop example01.ps

example01: example01.c ../pstool.c
	cc example01.c ../pstool.c -o example01


example02.pdf: example02
	./example02
	gs -o example02.pdf -sDEVICE=pdfwrite -dEPSCrop example02.ps

example02: example02.c ../pstool.c
	cc example02.c ../pstool.c -o example02


example03.pdf: example03
	./example03
	gs -o example03.pdf -sDEVICE=pdfwrite -dEPSCrop example03.ps

example03: example03.c ../pstool.c
	cc example03.c ../pstool.c -o example03



