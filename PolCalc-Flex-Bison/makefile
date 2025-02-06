CC = gcc
CFLAGS = -std=c18
TARGET = polcal_test
SRCS = Calculator.tab.c lex.yy.c

all: $(TARGET) run

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

Calculator.tab.c: Calculator.y
	bison -d Calculator.y 

lex.yy.c: scanner.l
	flex scanner.l

run: expresiones.txt
	$(TARGET) < expresiones.txt

clean:
	del -f $(OBJS)

# clean:
# 	rm -f $(OBJS)