NAME = ircserv
INCDIR = include
OBJDIR = .obj
SRCDIR = app
CMDDIR = cmd
FCTDIR = fct

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I $(SRCDIR)/$(INCDIR) -I $(CMDDIR)/$(INCDIR)
DEPFLAGS = -MM -MP

SRCS_APP = \
	$(SRCDIR)/Channel.cpp \
	$(SRCDIR)/Server.cpp \
	$(SRCDIR)/Client.cpp

SRCS_CMD = \
	$(CMDDIR)/Join.cpp \
	$(CMDDIR)/Topic.cpp \
	$(CMDDIR)/Test1.cpp \
	$(CMDDIR)/Request.cpp \
	$(CMDDIR)/Maker.cpp \
	$(CMDDIR)/Makerj.cpp \
	$(CMDDIR)/Prefix.cpp \
	$(CMDDIR)/split.cpp

SRCS_FCT = \
	$(FCTDIR)/fct.cpp

SRCS = $(SRCS_APP) $(SRCS_CMD)


OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_APP)) \
		$(patsubst $(FCTDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_FCT)) \
       $(patsubst $(CMDDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_CMD))

DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(SRCDIR)/main.cpp -o $(NAME)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)      
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.o: $(CMDDIR)/%.cpp
	@mkdir -p $(dir $@)      
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.o: $(FCTDIR)/%.cpp
	@mkdir -p $(dir $@)      
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

me: all
	./$(NAME) 6667 jj

titi: all
	./$(NAME) 6666 pp

.PHONY: all clean fclean re me titi

