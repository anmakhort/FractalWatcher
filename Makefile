#################################################################
# Author: Anatolii MAKHORT
# e-mail: anmakhort@gmail.com
#################################################################

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
#TARGET_VERBOSE = -D_VERBOSE
DEFINES = -D_XOPEN_SOURCE
INCLUDES = -I/usr/include -I/usr/X11/include
LDFLAGS = -L../../minilibx/ -lmlx -L/usr/lib -lXext -lX11 -lm -lpng
LIBS =

TARGET = graphics
SOURCES = graphics.c mlx_screenshot.c helpwnd.c
OBJECTS = $(SOURCES:.c=.o)

RM = rm -fr
MK = mkdir -p

.PHONY: all, run, clean, distclean, objclean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) $(DEFINES) $(TARGET_VERBOSE) $(DEBUG) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

distclean:
	@$(RM) $(TARGET)

objclean:
	@$(RM) $(OBJECTS)

clean: distclean objclean