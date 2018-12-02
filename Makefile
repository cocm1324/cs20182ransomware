CC=gcc
TARGET=a.out
OBJS=main.o des.o util.o ransomware.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm *.o
	rm $(TARGET)
 
