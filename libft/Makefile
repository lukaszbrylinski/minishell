SRCS = ft_absolute.c ft_atoi.c ft_isascii.c ft_memmove.c ft_strlcat.c \
ft_bzero.c ft_isdigit.c ft_memset.c ft_strlcpy.c ft_strtrim.c \
ft_isprint.c ft_strchr.c ft_strlen.c ft_substr.c \
ft_calloc.c ft_memchr.c ft_strndup.c ft_strdup.c ft_strncmp.c ft_tolower.c \
ft_isalnum.c ft_memcmp.c ft_strnstr.c ft_toupper.c \
ft_isalpha.c ft_memcpy.c ft_strjoin.c ft_strrchr.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
get_next_line_bonus.c ft_printf.c ft_printf_utils.c ft_printf_writing.c ft_free_split.c

SRCSB = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
ft_lastadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
ft_lstmap_bonus.c

OBJS = ${SRCS:.c=.o}
OBJSB = ${SRCSB:.c=.o}
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I ../include

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		@${LIBC} ${NAME} ${OBJS}

bonus: ${NAME} ${OBJSB}
	@${LIBC} ${NAME} ${OBJSB}

all: ${NAME}

clean:
	@${RM} ${OBJS} ${OBJSB}

fclean: clean
	@${RM} ${NAME} ${bonus}

re: fclean all

.PHONY: all clean fclean re
