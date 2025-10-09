NAME = request
CC = c++
FLAG = -Wall -Wextra -Werror -std=c++98 -g3 -MMD

SRC =	main.cpp Request.cpp Prefix.cpp Topic.cpp split.cpp
		
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEPS = $(OBJS:.o=.d)

all : $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(FLAG) -c $< -o $@

$(NAME): Makefile $(OBJS)
	${CC} ${FLAG} -o $@ $(OBJS)

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

me: all
	./$(NAME)

.PHONY: all clean fclean re me

-include $(DEPS)