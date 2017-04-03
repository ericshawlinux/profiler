CC       := gcc
CFLAGS   := -Wall -Wextra
INCLUDES := -I./src -I./src/cli -I./src/record -I./src/record/filter
OBJECTS  := obj/pfr_cmd.o obj/pfr_usage.o obj/pfr_disk.o obj/pfr_list.o obj/pfr_type.o obj/pfr_detail.o obj/pfr_filter.o obj/main.o
EXENAME  := profiler

vpath %.c src src/cli src/record src/record/filter

$(EXENAME): $(OBJECTS)
	$(CC) $(INCLUDES) $^ -o $@

obj/%.o: %.c
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	rm -vf $(OBJECTS)
	rm -vf $(EXENAME)
	rm -vf $(EXENAME).exe

touch:
	touch data/types.dat data/types.tmp
	touch data/profiles.dat data/profiles.tmp

trunc:
	truncate --size 0 data/types.dat data/types.tmp
	truncate --size 0 data/profiles.dat data/profiles.tmp
