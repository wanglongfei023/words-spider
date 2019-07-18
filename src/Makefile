CC=gcc
INCLUDE=-I../include/
CFLAGS=-c -g -Wall $(INCLUDE)
CPPFLAGS=-E -D
LDFLAGS=-lssl -lcrypto -lpthread
TARGET=app
SRCFILE=$(wildcard *.c)
DESFILE=$(patsubst %.c,%.o,$(SRCFILE))
RM=-rm -rf

$(TARGET):$(DESFILE)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) $<

output:
	@echo "$(SRCFILE)"
	@echo "$(DESFILE)"

clean:
	$(RM) $(DESFILE)
	$(RM) $(TARGET)
