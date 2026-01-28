# ===================== Project =====================
NAME      := minishell
OBJDIR    := OBJECTS

# ===================== Tools =======================
CC        := cc
RM        := rm -rf
MKD       := mkdir -p

# ===================== Flags =======================
CFLAGS    := -Wall -Wextra -Werror -fsanitize=address -g3
MAKEFLAGS += --silent

# ===================== Dirs ========================
LIBFT_DIR := libft
PIPEX_DIR := pipex
INC_DIR   := includes

# ===================== Includes / Libs =============
INCLUDES  := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(PIPEX_DIR)
LIBFT_A   := $(LIBFT_DIR)/libft.a
PIPEX_A   := $(PIPEX_DIR)/pipex.a
LIBS      := -lreadline $(PIPEX_A) -L$(LIBFT_DIR) -lft

# ===================== Colors =======================
RED       := \033[91;1m
GREEN     := \033[92;1m
CLEAR     := \033[0m

# ===================== Sources ======================
SRC_PARSE := \
	src/parse/main.c \
	src/parse/parse.c \
	src/parse/parser_helpers.c

SRC_UTILS := \
	src/utils/mini_utils.c \
	src/utils/signals.c \
	src/utils/minishell_cleanup.c \
	src/utils/ft_split_quotes.c

SRC_ENV := \
	src/env/vars_init.c \
	src/env/env_utils.c

SRC_BUILTINS := \
	src/builtins/others_built.c \
	src/builtins/unset_built.c \
	src/builtins/export_built.c \
	src/builtins/export_utils.c \
	src/builtins/export_helpers.c \
	src/builtins/cd_built.c \
	src/builtins/cd_utils.c \
	src/builtins/exit_built.c \
	src/builtins/echo_built.c

SRC_EXPAND := \
	src/expand/expansor.c \
	src/expand/expansor_helpers.c \
	src/expand/expansor_helpers_2.c \
	src/expand/exp_exit_var.c

SRC_PIPE := \
	src/pipe/pipe_entry.c \
	src/pipe/pipe_runtime.c \
	src/pipe/pipe_syntax.c \
	src/pipe/pipe_trim.c \
	src/pipe/pipe.c


SRC := $(SRC_PARSE) $(SRC_UTILS) $(SRC_ENV) $(SRC_BUILTINS) $(SRC_EXPAND) $(SRC_PIPE)
OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# ===================== Rules ========================
all: $(NAME)

$(NAME): $(LIBFT_A) $(PIPEX_A) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@echo "$(GREEN)Minishell activated$(CLEAR)"

$(OBJDIR)/%.o: %.c
	@$(MKD) $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(PIPEX_A):
	@$(MAKE) -C $(PIPEX_DIR)

clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(PIPEX_DIR)
	@echo "$(RED)Clean done$(CLEAR)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(PIPEX_DIR)
	@echo "$(RED)FClean done$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re
