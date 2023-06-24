CC = clang
CFLAGS = -O3 -march=alderlake

SRCS = main.c Deoxys.c
EXECUTABLE = Deoxys
OUTPUT_FILE = output
REF_OUTPUT_FILE = ref-output

.PHONY: all clean test

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

test: $(EXECUTABLE)
	make clean
	make
	./$(EXECUTABLE) < input > $(OUTPUT_FILE)
	diff $(OUTPUT_FILE) $(REF_OUTPUT_FILE)

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OUTPUT_FILE)
