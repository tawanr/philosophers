# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 09:24:00 by tratanat          #+#    #+#              #
#    Updated: 2022/04/24 11:04:06 by tratanat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/

INCS = -Iincludes/
NAME = philo_bonus
SRCS = main_bonus.c philo_err_bonus.c philo_init_bonus.c philo_utils_bonus.c \
		philo_output_bonus.c ft_atoi_bonus.c \
		philo_cleanup_bonus.c philo_counter_bonus.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJS))
	$(CC) $(INCS) $^ -o $(NAME) -lpthread
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(INCS) -o $@
clean:
	$(RM) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all