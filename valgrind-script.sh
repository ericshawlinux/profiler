#!/bin/bash

valgrind --leak-check=full ./profiler
valgrind --leak-check=full ./profiler help

# type define
valgrind --leak-check=full ./profiler def
valgrind --leak-check=full ./profiler def valgrind1 "text"
valgrind --leak-check=full ./profiler def valgrind2 "date"
valgrind --leak-check=full ./profiler def valgrind3 "number"

# type show
valgrind --leak-check=full ./profiler show
valgrind --leak-check=full ./profiler show --type-id 1
valgrind --leak-check=full ./profiler show --type-id-gte 1
valgrind --leak-check=full ./profiler show --type-id-lte 5
valgrind --leak-check=full ./profiler show --type-id-gt 1
valgrind --leak-check=full ./profiler show --type-id-lt 5
valgrind --leak-check=full ./profiler show --data-type "text"
valgrind --leak-check=full ./profiler show --data-type "date"
valgrind --leak-check=full ./profiler show --data-type "number"
valgrind --leak-check=full ./profiler show --type-name "valgrind1"
valgrind --leak-check=full ./profiler show --type-name-contains "valgrind"
valgrind --leak-check=full ./profiler show --type-name-starts-with "v"

# detail new
valgrind --leak-check=full ./profiler new
valgrind --leak-check=full ./profiler new valgrind1 "testing value"
valgrind --leak-check=full ./profiler new valgrind2 "2014-08-25"
valgrind --leak-check=full ./profiler new --profile-id 1 "valgrind3" 999

# detail update (not implemented)
valgrind --leak-check=full ./profiler update

# detail get
valgrind --leak-check=full ./profiler get

# type undef
valgrind --leak-check=full ./profiler undef
valgrind --leak-check=full ./profiler undef "valgrind1"
valgrind --leak-check=full ./profiler undef "valgrind2"
valgrind --leak-check=full ./profiler undef --type-id 3