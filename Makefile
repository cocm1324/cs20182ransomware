CC=gcc
TARGET=a.out
OBJS=main.o des.o util.o fileio.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm *.o
	rm $(TARGET)
 
