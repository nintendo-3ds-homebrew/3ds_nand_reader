##################################_COMPILATION_#################################
NAME	= 3ds_nand_reader
CC		= clang
FLAG	= -Weverything
SRCS	=	./source/main.c

OBJS	= $(SRCS:.c=.o)

INCLUDE	= -I ./include
###########################_RELINK_MODIFY_.h####################################
RELINK = ./include/3ds_nand_reader.h
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAG) -o $(NAME) $(OBJS) $(LFT)
	@printf "✅  Compilation done.\n"
	#@chmod u+s ./3ds_nand_reader

%.o : %.c $(RELINK) ./Makefile
	@printf " ✅                                                              \r"
	@printf "✅  $(notdir $<)\r"
	@$(CC) -c $(FLAG) $< -o $@ $(INCLUDE)

clean:
	@printf "                                                               \r"
	@printf "✅  clean done !\n"
	@rm -f $(OBJS)

fclean:
	@printf "                                                               \r"
	@printf "✅  fclean done !\n"
	@rm -f $(NAME) $(OBJS)

re: fclean all

