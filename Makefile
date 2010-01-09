LIBS = -lsuinput -ludev `pkg-config --libs libhid`
CFLAGS = -Wall

all: gkos

gkos: gkos.c gkos.h
	gcc $(CFLAGS) $(LIBS) gkos.c -o gkos

clean:
	rm -f *.o gkos