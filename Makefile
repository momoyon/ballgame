LIBS=-lm -lraylib -L./
CFLAGS=-Wextra -Wall -I./include -Wno-sign-compare -Wno-unused-value -Wno-unused-variable

ballgame: *.c
	cc -o $@ *.c $(CFLAGS) $(LIBS)
