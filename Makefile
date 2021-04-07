SRCFOLD		= srcs/
BONUSFOLD	= srcs_bonus/

SRCS_BONUS	= ${BONUSFOLD}parser.c \
			${BONUSFOLD}main.c \
			${BONUSFOLD}parser_elements.c \
			${BONUSFOLD}parser_map.c \
			${BONUSFOLD}cub_init.c \
			${BONUSFOLD}cub_init2.c \
			${BONUSFOLD}utils.c \
			${BONUSFOLD}utils2.c \
			${BONUSFOLD}utils3.c \
			${BONUSFOLD}utils4.c \
			${BONUSFOLD}draw.c \
			${BONUSFOLD}draw_utils.c \
			${BONUSFOLD}movement.c \
			${BONUSFOLD}generate_bmp_file.c \
			${BONUSFOLD}raycast.c \
			${BONUSFOLD}raycast_sprite.c \
			${BONUSFOLD}ray_intersect.c \
			${BONUSFOLD}run_cub.c \
			${BONUSFOLD}get_pixels.c \
			${BONUSFOLD}minimap.c

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
			${SRCFOLD}movement.c \
			${SRCFOLD}generate_bmp_file.c \
			${SRCFOLD}raycast.c \
			${SRCFOLD}raycast_sprite.c \
			${SRCFOLD}ray_intersect.c \
			${SRCFOLD}run_cub.c \
			${SRCFOLD}get_pixels.c \

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME		= cub3D

NAME_BONUS	= cub3D_bonus

CC			= @gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= @rm -f

%.o: %.c
	${CC} ${CFLAGS} -I/usr/include -Imlx_linux -Ilibft -Iincludes -c $< -o ${<:.c=.o}

${NAME}:		 ${OBJS}
	@echo "Compiling ressources needed to create the executable.It should take few seconds.."
	@make --no-print-directory -C mlx_linux
	@make --no-print-directory -C libft
	@${CC} ${CFLAGS} ${OBJS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Llibft -Imlx_linux -lft -lXext -lX11 -lm -lz -o ${NAME}
	@echo "Game is ready to be launched\n\nTo launch, type \"cub3D file.cub\"\nUse --save option to save the first frame of the game into a bitmap that will be stored into saves/ directory"

${NAME_BONUS}:		 ${OBJS_BONUS}
	@echo "Compiling ressources needed to create the executable.It should take few seconds.."
	@make --no-print-directory -C mlx_linux
	@make --no-print-directory -C libft
	@${CC} ${CFLAGS} ${OBJS_BONUS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Llibft -Imlx_linux -lft -lXext -lX11 -lm -lz -o ${NAME_BONUS}
	@echo "Game is ready to be launched\n\nTo launch, type \"cub3D_bonus file.cub\"\nUse --save option to save the first frame of the game into a bitmap that will be stored into saves/ directory"

all:			${NAME}

bonus:			${NAME_BONUS}

clean:
	@echo "Cleaning files"
	${RM} ${OBJS}
	@make clean --no-print-directory -C libft/

clean_bonus:
	@echo "Cleaning files"
	${RM} ${OBJS_BONUS}
	@make clean --no-print-directory -C libft/

fclean:			clean
	${RM} ${NAME}
	@make clean --no-print-directory  -C mlx_linux/
	@make fclean --no-print-directory -C libft/

fclean_bonus:			clean_bonus
	${RM} ${NAME_BONUS}
	@make clean --no-print-directory  -C mlx_linux/
	@make fclean --no-print-directory -C libft/

re:				fclean all

re_bonus:		fclean_bonus bonus

.PHONY:			all clean fclean re bonus clean_bonus fclean_bonus re_bonus
