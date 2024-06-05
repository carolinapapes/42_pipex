# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c parser.c pipex.c commands.c
BUILD_DIR = ./build

# LIBS
LIBS_PATH = ./libs

# Libft
LIBFT_NAME = libft
LIBFT_PATH 	= $(LIBS_PATH)/libft
LIBFT_LINK	= -L${LIBFT_PATH} -lft

OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DPS = $(OBJ:%.o=%.d) $(OBJ_SRC_BONUS:%.o=%.d)


PREQ = Makefile 
NAME = pipex
DEFLAGS := -MMD -MP

#Colors
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

$(NAME): $(OBJ) $(LIBFT_PATH)/libft.a
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_LINK)
	@echo "$(GREEN)📚completed		$(NAME)$(DEF_COLOR)"


$(BUILD_DIR)/%.o: %.c $(PREQ) | $(BUILD_DIR) 
	@$(CC) $(CFLAGS) $(DEFLAGS) -c $< -o $@
	@echo "$(GRAY)⏳compiling		$<$(DEF_COLOR)"
	
$(BUILD_DIR):
	@mkdir -p $@

$(BONUS_FILE): 
	@touch .bonus

clean:
	@rm -rf $(BUILD_DIR)
	@Make -C $(LIBFT_PATH) clean
	@echo "$(RED)🧹clean		${NAME}$(DEF_COLOR)"

fclean:
	@rm -f $(NAME)
	@- rm .bonus
	@rm -rf $(BUILD_DIR)
	@Make -C $(LIBFT_PATH) fclean
	@echo "$(RED)🧹fclean		${NAME}$(DEF_COLOR)"

re: fclean all

-include $(DPS)

.PHONY: re fclean clean all make_libs bonus