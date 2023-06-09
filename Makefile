NAME = cryp
CC = gcc

# if you use mac
# INCLUDE_MAC=-I/opt/homebrew/opt/openssl@3/include
# LINK_MAC=-L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
LINK = -lssl -lcrypto

INCLUDE = -I./include

SRCS_DIR = ./src
SRCS = src/main.c \
		src/cryp.c \
		src/file.c \
		src/hmac.c \
		src/parse.c \
		src/print.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LINK)

%.o : %.c
	$(CC) $(INCLUDE) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : 
	make fclean
	make all

.PHONY: all clean fclean re
