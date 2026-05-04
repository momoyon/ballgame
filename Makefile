LIBS=-lm -lraylib -L./
CFLAGS=-Wextra -Wall -I./include -Wno-sign-compare -Wno-unused-value -Wno-unused-variable

all: ballgame asset_packer

ballgame: main.c config.c ball.c control_nob.c
	cc -o $@ $^ $(CFLAGS) $(LIBS)

asset_packer: ./asset_packer.c
	rm -rf ./include/packed.old/
	cc -o $@ asset_packer.c $(CFLAGS) $(LIBS)

.PHONY: asset_packer
