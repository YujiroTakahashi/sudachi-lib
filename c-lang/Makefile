EXEC = sample
CC = gcc
#LDFLAGS = -lsudachi
LDFLAGS = -L$(LD_LIBRARY_PATH) -lsudachi
COMMON = -Iinclude/
CFLAGS = -Wall
OBJS = main.o

all: $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

main.o: src/main.c
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(EXEC)
