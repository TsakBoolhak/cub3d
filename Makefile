SRCFOLD		= srcs/

SRCS		= ${SRCFOLD}parser.c \
			${SRCFOLD}main.c \
			${SRCFOLD}parser_elements.c \
			${SRCFOLD}parser_map.c \
			${SRCFOLD}cub_init.c \
			${SRCFOLD}cub_init2.c \
			${SRCFOLD}utils.c \
			${SRCFOLD}utils2.c \
			${SRCFOLD}utils3.c \
			${SRCFOLD}draw.c \
			${SRCFOLD}draw_utils.c \
			${SRCFOLD}movement.c \
			${SRCFOLD}generate_bmp_file.c \
			${SRCFOLD}raycast.c \
			${SRCFOLD}raycast_sprite.c \
			${SRCFOLD}ray_intersect.c \
			${SRCFOLD}run_cub.c \
			${SRCFOLD}get_pixels.c \
			${SRCFOLD}minimap.c

OBJS		= ${SRCS:.c=.o}

NAME		= cub3d

CC			= @gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= @rm -f

%.o: %.c
	${CC} ${CFLAGS} -I/usr/include -Imlx_linux -Ilibft -Iincludes -c $< -o ${<:.c=.o}

${NAME}:		 ${OBJS}
	@${RM} saves/deleteme
	@echo "Compiling ressources needed to create the executable.It should take few seconds.."
	@make --no-print-directory -C mlx_linux
	@make --no-print-directory -C libft
	${CC} ${CFLAGS} ${OBJS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Llibft -Imlx_linux -lft -lXext -lX11 -lm -lz -o ${NAME}
	@echo "Game is ready to be launched\n\nTo launch, type \"${NAME} file.cub\"\nIf you add --save option, it will save an image representing the first frame of the game into a .bmp file stored in saves/ directory"

all:			${NAME}

clean:
	@echo "Cleaning files"
	${RM} ${OBJS}
	@make clean --no-print-directory -C libft/

fclean:			clean
	${RM} ${NAME}
	@make clean --no-print-directory  -C mlx_linux/
	@make fclean --no-print-directory -C libft/

re:				fclean all

.PHONY:			all clean fclean re
