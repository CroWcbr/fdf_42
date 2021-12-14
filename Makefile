# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 16:20:28 by cdarrell          #+#    #+#              #
#    Updated: 2021/10/30 20:05:07 by cdarrell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

CC			=	gcc -g3
FLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	=	libft
LIBFT_LIB	=	libft.a

MLX_LIB		=	libmlx.a
MLX_DIR		=	./minilibx_macos/
MLX_INC		=	-I ${MLX_DIR}
MLX			=	-L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

HEADER		=	fdf.h
SRC			=	fdf.c \
				fdf_parsing_map.c \
				fdf_parsing_list.c \
				fdf_libft_add.c \
				fdf_draw.c \
				fdf_unit_vector.c \
				fdf_hook_projection.c \
				fdf_hook.c \
				fdf_hook_mouse.c \
				fdf_hook_rotate.c \
				fdf_print_menu.c 

OBJ_DIR		=	obj
OBJ 		=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

INCLUDES	= 	-I .

${NAME}:	${OBJ}
#			@make -C ${MLX_DIR} all
#			@echo "\tCompiling...\t" [ $(MLX_LIB) ] $(SUCCESS)
			@make -C ${LIBFT_DIR}/ all
			@$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(MLX) ${LIBFT_DIR}/${LIBFT_LIB}
			@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)
									
$(OBJ)		:	| $(OBJ_DIR)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o :	%.c $(HEADER) Makefile
					@${CC} $(FLAGS) $(INCLUDES) $(MLX_INC) -o $@ -c $<

#COLORS
C_NO="\033[00m"
C_OK="\033[32m"
C_GOOD="\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)
			
all:	$(NAME)

bonus:	$(NAME)

clean:
		@make -C ${LIBFT_DIR}/ clean
#		@make -C ${MLX_DIR} clean > /dev/null	
#		@echo "\tCleaning...\t" [ $(MLX_LIB) ] $(OK)		
		@${RM_DIR} ${OBJ_DIR}
		@echo "\tCleaning...\t" [ $(NAME) ] $(OK)
		
fclean:	
		@make -C ${LIBFT_DIR}/ fclean
#		@make -C ${MLX_DIR}/ clean > /dev/null
#		@echo "\tCleaning...\t" [ $(MLX_LIB) ] $(OK)		
		@${RM_DIR} ${OBJ_DIR}
		@echo "\tCleaning...\t" [ $(NAME) ] $(OK)
		@${RM_FILE} $(NAME)
		@echo "\tDeleting...\t" [ $(NAME) ] $(OK)
		
re:		fclean all

.PHONY: all bonus clean fclean re
