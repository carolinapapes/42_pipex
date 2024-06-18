# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./include
SRC_DIR = ./src
SRC = main.c \
parser.c \
px_err.c \
px_exit.c \
px_fd_handler.c \
px_fd.c \
px_cmd.c \
px_process__exec.c \
px_process__fd.c \
px_process__init.c \
px_process__utils.c \
px_process__wait.c \
px_process.c \
px_program.c \
utils.c \

BUILD_DIR = ./build

# LIBS
LIBS_PATH = ./libs

# Libft
LIBFT_NAME = libft
LIBFT_PATH 	= $(LIBS_PATH)/libft
LIBFT_LINK	= -L${LIBFT_PATH} -lft

OBJ_SRC = $(SRC:%.c=$(BUILD_DIR)/%.o)
DPS = $(OBJ_SRC:%.o=%.d)

PREQ = Makefile
NAME = pipex
DEFLAGS := -MMD -MP

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m

# Functions
define make_lib
    @echo "Making $1..."
    @make -C $2 
    @echo "$(GREEN)📚completed		$1$(DEF_COLOR)"
endef

all: make_libs $(NAME)

make_libs:
	$(call make_lib,$(LIBFT_NAME),$(LIBFT_PATH))

$(NAME): $(OBJ_SRC) $(LIBFT_PATH)/libft.a
	@$(CC) $(CFLAGS) $(OBJ_SRC) -o $(NAME) $(LIBFT_LINK)
	@echo "$(GREEN)📚completed		$(NAME)$(DEF_COLOR)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(PREQ) | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(DEFLAGS) -c $< -o $@
	@echo "$(GRAY)⏳compiling		$<$(DEF_COLOR)"
	
$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_PATH) clean
	@echo "$(RED)🧹clean		${NAME}$(DEF_COLOR)"

fclean:
	@rm -f $(NAME)
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(RED)🧹fclean		${NAME}$(DEF_COLOR)"

re: fclean all

-include $(DPS)

.PHONY: re fclean clean all make_libs
