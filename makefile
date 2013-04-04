game: game.c
	gcc -o game -lm -fopenmp -L/usr/lib -lGLU  -lGL -lglut  -L/usr/X11R6/lib -lX11 -lXext -lXi -lXmu game.c
