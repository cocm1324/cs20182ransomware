CC=gcc
TARGET=a.out
OBJS=main.o des.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm *.o
	rm $(TARGET)
 
