NAME = minishell

RED		=	\033[91;1m
GREEN	=	\033[92;1m
CLEAR	=	\033[0m

MKD = mkdir -p
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

MK_LIBFT = $(MAKE) -s -C libft 
MK_PIPEX = $(MAKE) -s -C pipex 

INCLUDES = -I. -Ilibft/libft -Ipipex/pipex

LIBS = -lreadline pipex/pipex.a -Llibft -lft

SRCs =	parse.c	\
		builts_in_2.c \
		mini_utils.c \
# 		builts_in_1.c \

MAKEFLAG += --silent

DIR_OBJs = OBJECTS
OBJs = $(addprefix $(DIR_OBJs)/,$(SRCs:%.c=%.o))

all: dir_lib dir_pipex dir_objs $(NAME)

$(NAME): $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(NAME) $(LIBS)
	@echo "$(GREEN)Minishell activated"

$(DIR_OBJs)/%.o: %.c | $(DIR_OBJs)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIR_OBJs):
	$(MKD) $(DIR_OBJs)

dir_lib:
	@$(MK_LIBFT)

dir_pipex:
	@$(MK_PIPEX)

clean:
	$(RM) $(NAME)           
	$(RM) $(OBJs)              
	$(RM) $(DIR_OBJs)         
	@$(MAKE) clean -C libft > /dev/null 2>&1
	@$(MAKE) clean -C pipex > /dev/null 2>&1
	@echo "$(RED) Clean done"

fclean: clean
	@$(MAKE) fclean -C libft > /dev/null 2>&1
	@$(MAKE) fclean -C pipex > /dev/null 2>&1
	@echo "$(RED) FClean done"

re: fclean all

.PHONY: all clean fclean re dir_objs dir_lib dir_pipex
