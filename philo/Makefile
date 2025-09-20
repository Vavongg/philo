# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 16:33:10 by ainthana          #+#    #+#              #
#    Updated: 2025/09/20 13:24:28 by ainthana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = \
	srcs/main.c \
	srcs/parsing.c srcs/init.c \
	srcs/utils.c srcs/sync_utils.c srcs/utils_err.c \
	srcs/simulation.c srcs/routine.c srcs/monitoring.c srcs/clean.c\

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# ───── Couleurs ─────
RESET = \033[0m
BOLD = \033[1m
GREEN = \033[32m
RED = \033[31m
CYAN = \033[36m
BLUE = \033[34m

# ───── Rules ─────
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/srcs
	@echo "$(CYAN)➤ Dossiers objets prêts.$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@
	@echo "$(GREEN)✔ $(NAME) compilé avec succès.$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iinc -c $< -o $@
	@echo "$(BLUE)• Compilation : $<$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✘ Fichiers objets nettoyés.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✘ Exécutable supprimé.$(RESET)"

re: fclean all

.PHONY: all clean fclean re


