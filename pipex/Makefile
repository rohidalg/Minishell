NAME = pipex

MKL = make -s -C ../libft
MK = make -s
MKD = mkdir -p
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g3

INCLUDES = -I ../libft

SRCs = pipex.c	\
		env_check.c	\
		ft_utils.c \
		redirects.c

DIR_OBJs = OBJECTS

OBJs = $(addprefix $(DIR_OBJs)/,$(SRCs:%.c=%.o))

all: dir_lib dir_objs pipex.a

pipex.a: $(OBJs)
	@ar rcs pipex.a $(OBJs)

$(DIR_OBJs)/%.o: %.c | $(DIR_OBJs)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIR_OBJs):
	@$(MKD) $(DIR_OBJs)

dir_lib:
	@$(MKL)

clean:
	$(RM) $(NAME)   
	@$(RM) $(DIR_OBJs)
	@$(MK) clean -C ../libft

fclean: clean
	@$(RM) pipex.a
	@$(MK) fclean -C ../libft

re: fclean all

.PHONY: all clean fclean re dir_lib dir_objs


