##
## Makefile for my_printf in /home/diot-_c/my_printf
## 
## Made by cyprien diot-
## Login   <diot-_c@epitech.net>
## 
## Started on  Fri Nov 14 18:19:01 2008 cyprien diot-
## Last update Thu Mar 25 18:13:06 2010 romain bellan
##

OSTYPE			= $(shell uname -s)

SRC			= malloc.c \
			  free.c \
			  realloc.c \
			  show_mem.c \
			  utils.c \
			  utils_mem.c \
			  config_malloc.c

OBJ			= $(SRC:.c=.o)

CC_SUN			= /usr/sfw/bin/gcc

NAME			= libmy_malloc_$(OSTYPE).so

NAME_LINK		= libmy_malloc.so

CC			= gcc

CFLAGS			= -Werror -W -pedantic -Wall -fPIC

RM			= rm -f

all:			$(OSTYPE)
			ln -s $(NAME) $(NAME_LINK)

FreeBSD:		$(OBJ)
			gcc -shared -o $(NAME) $(OBJ)

Linux:			$(OBJ)
			gcc -shared -o $(NAME) $(OBJ)

dev:
			cc -g $(SRC) main.c -o tst_malloc

solaris:
			$(CC_SUN) -fpic -c $(SRC)
			$(CC_SUN) -shared -o $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ)
			$(RM) *~

fclean:			clean
			$(RM) $(NAME)
			$(RM) $(NAME_LINK)

re:			fclean all

redev:			fclean dev
