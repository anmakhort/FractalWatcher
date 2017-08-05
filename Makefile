#################################################################
# Makefile for 'Fractal Watcher' GUI application
# Author: Anatolii MAKHORT
# e-mail: anmakhort@gmail.com
#################################################################

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O3 -g
TARGET_VERBOSE =
DEFINES = -D_XOPEN_SOURCE
INCLUDES = -I/usr/include -I/usr/X11/include -I/include
LDFLAGS = -L./minilibx/ -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lpng
LIBS =

NAME = fractwtcher
VERSION = v1.0
TARGET = $(NAME)_$(VERSION)
TARGETDIR = release

SOURCES = 	src/graphics.c \
			src/cleanup.c \
			src/mlx_screenshot.c \
			src/helpwnd.c \
			src/render.c \
			src/filler.c \
			src/mousehandler.c \
			src/savingdir.c \
			src/loop.c \
			src/keyreleased.c \
			src/endiannes.c \
			src/transform.c

OBJECTS = $(SOURCES:.c=.o)

RM = rm -fr

.PHONY: install_requirements, all, debug, release, run, clean, distclean, objclean, imgclean

install_requirements:
	sudo apt-get install xorg libx11-dev

all: install_requirements release

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@$(CC) -o $(TARGETDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) $(DEFINES) $(TARGET_VERBOSE) $(DEBUG) -c $< -o $@

debug: TARGET_VERBOSE = -D_VERBOSE
debug: TARGETDIR = debug
debug: clean $(TARGET)
	@$(RM) $(OBJECTS)

release: clean $(TARGET)
	@$(RM) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

distclean:
	@$(RM) $(TARGETDIR)/$(TARGET)

objclean:
	@$(RM) $(OBJECTS)

imgclean:
	@$(RM) Images

clean: distclean objclean