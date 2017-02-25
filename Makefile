CFLAGS=-Wall -Wextra
EXENAME=profiler

ifeq ($(OS),Windows_NT)
	SHELL=C:/Windows/System32/cmd.exe
endif

profiler: src/*.c src/*.h
	gcc $(CFLAGS) -o $(EXENAME) src/main.c -I./src/

debug: src/*.c src/*.h
	gcc $(CFLAGS) -g -o $(EXENAME) src/main.c -I./src/

check:
	gcc $(CFLAGS) -c -I./src src/main.c
	gcc $(CFLAGS) -c -I./src src/pfr_config.h
	gcc $(CFLAGS) -c -I./src src/pfr_type.c
	gcc $(CFLAGS) -c -I./src src/pfr_type.h
	gcc $(CFLAGS) -c -I./src src/pfr_detail.c
	gcc $(CFLAGS) -c -I./src src/pfr_detail.h
	gcc $(CFLAGS) -c -I./src src/pfr_disk.c
	gcc $(CFLAGS) -c -I./src src/pfr_usage.c

clean:
	rm -vf *.o src/*.o src/*.gch
	rm -vf $(EXENAME)
	rm -vf $(EXENAME).exe

touch:
	touch data/types.dat data/types.tmp
	touch data/profiles.dat data/profiles.tmp

trunc:
	truncate --size 0 data/types.dat data/types.tmp
	truncate --size 0 data/profiles.dat data/profiles.tmp
