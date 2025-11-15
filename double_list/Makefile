CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
TARGETS = test

SRCS_TEST = test.c elmt_t.c double_list.c
OBJS_TEST = $(SRCS_TEST:.c=.o)

all: $(TARGETS)

test: $(OBJS_TEST)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS_TEST)

fclean: clean
	rm -f $(TARGETS)

re: fclean all

.PHONY: all clean fclean re
