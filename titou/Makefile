NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I incl -I incl/cmd
DEPFLAGS = -MM -MP

SRCDIR = src
CMDDIR = $(SRCDIR)/cmd
INCDIR = incl
OBJDIR = obj

SRCS = \
	$(SRCDIR)/main.cpp \
	$(SRCDIR)/channel.cpp \
	$(SRCDIR)/server.cpp \
	$(SRCDIR)/client.cpp \
	$(CMDDIR)/Join.cpp \
	$(CMDDIR)/Topic.cpp \
	$(CMDDIR)/Test1.cpp \
	$(CMDDIR)/Request.cpp \
	$(CMDDIR)/Makern.cpp \
	$(CMDDIR)/Prefix.cpp \
	$(CMDDIR)/split.cpp \

OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)      
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

