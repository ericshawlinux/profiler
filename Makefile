CC       := gcc
CFLAGS   := -Wall -Wextra
INCLUDES := -I./src -I./src/cli -I./src/record -I./src/record/filter
OBJECTS  := obj/pfr_files.o obj/pfr_cmd.o obj/pfr_usage.o obj/pfr_disk.o obj/pfr_list.o obj/pfr_type.o obj/pfr_detail.o obj/pfr_filter.o obj/main.o
EXENAME  := profiler

vpath %.c src src/cli src/record src/record/filter

$(EXENAME): $(OBJECTS)
	$(CC) $(INCLUDES) $(CFLAGS) $^ -o $@

obj/%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -vf $(OBJECTS)
	rm -vf $(EXENAME)
	rm -vf $(EXENAME).exe
