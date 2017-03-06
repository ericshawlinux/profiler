CFLAGS=-Wall -Wextra
EXENAME=profiler

profiler:
	gcc $(CFLAGS) -o $(EXENAME) src/main.c -I./src/

debug:
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
	gcc $(CFLAGS) -c -I./src src/pfr_list.c
	gcc $(CFLAGS) -c -I./src src/pfr_list.h
	gcc $(CFLAGS) -c -I./src src/pfr_filter.c
	gcc $(CFLAGS) -c -I./src src/pfr_filter.h

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
