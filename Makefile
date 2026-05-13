LIBS=-lm -lraylib -L./
CFLAGS=-Wextra -Wall -I./include -I./include/packed -Wno-sign-compare -Wno-unused-value -Wno-unused-variable -Wno-unused-but-set-variable

all: ballgame

ballgame: main.c config.c ball.c control_nob.c hole.c | asset_packer
	cc -o $@ $^ $(CFLAGS) $(LIBS)

asset_packer: ./asset_packer.c
	rm -rf ./include/packed.old/
	cc -o $@ asset_packer.c $(CFLAGS) $(LIBS)
	./asset_packer

clean:
	rm -rf ./asset_packer
	rm -rf ./ballgame

.PHONY: all
