LIBS=-lm -lraylib -L./
CFLAGS=-Wextra -Wall -I./include -Wno-sign-compare -Wno-unused-value

ballgame:
	cc -o $@ *.c $(CFLAGS) $(LIBS)
