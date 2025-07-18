NAME = minishell

MKD = mkdir -p
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

MK_LIBFT = $(MAKE) -s -C libft > /dev/null 2>&1
MK_PIPEX = $(MAKE) -s -C pipex > /dev/null 2>&1

INCLUDES = -I. -Ilibft/libft -Ipipex/pipex

LIBS = -lreadline -Llibft -lft pipex/pipex.a

SRCs = parse.c

DIR_OBJs = OBJECTS
OBJs = $(addprefix $(DIR_OBJs)/,$(SRCs:%.c=%.o))

all: dir_lib dir_pipex dir_objs $(NAME)

$(NAME): $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(NAME) $(LIBS)

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

fclean: clean
	@$(MAKE) fclean -C libft > /dev/null 2>&1
	@$(MAKE) fclean -C pipex > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re dir_objs dir_lib dir_pipex
