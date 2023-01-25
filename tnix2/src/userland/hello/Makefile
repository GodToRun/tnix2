# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=$(CRTS) hello.o $(STDLIBS)
CFLAGS=-nostdlib -fno-builtin -m32 -ffreestanding -I../stdlib/
LDFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf
TARGET=hello

all: $(SOURCES) link
	cp $(TARGET) ../../../

clean:
	-rm *.o $(TARGET)

link:
	ld $(LDFLAGS) -o $(TARGET) $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

include ../app.mk