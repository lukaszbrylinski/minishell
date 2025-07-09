#Variables

NAME		= minishell
INCLUDE		= include
LIBFT		= libft
LIBFT_A		= $(LIBFT)/libft.a
SRC_DIR		= src/
OBJ_DIR		= obj/
# TEST_DIR	= tests/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

SRC_FILES	=	token_functions tree_functions tokenizer parser readline

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

#Tests

# TEST_FILES	= 

# TEST_SRC	=	$(addprefix) $(TEST_DIR), $(addsuffix .c $(TEST_FILES))
# TEST_OBJ	=	$(addprefix) $(TEST_DIR), $(addsuffix .o $(TEST_FILES))

###

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@$(CC) $(OBJ) $(LIBFT_A) -lreadline -o $(NAME) 
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@make clean -C $(LIBFT)
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"
# 

fclean:		clean
			@$(RM) -f $(LIBFT)/libft.a
			@$(RM) -f $(NAME)
			@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)!$(DEF_COLOR)"

norm: