LIBS = -lsuinput -ludev `pkg-config --libs libhid`
CFLAGS = -Wall -g

all: gkos

gkos: main-linux.c gkos.c gkos.h
	gcc $(CFLAGS) $(LIBS) gkos.c main-linux.c -o gkos

clean:
	rm -f *.o gkos