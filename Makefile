# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/27 10:15:40 by brturcio          #+#    #+#              #
#    Updated: 2026/04/09 22:25:14 by brturcio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= ircserv
CC			:= c++
CFLAGS		:= -Wall -Wextra -Werror -std=c++98 -g

DIR_SRCS_M	:= sources/

DIR_OBJS_M	:= objs/

M_SOURCES	:=  main.cpp \
				Server.cpp \
				ServerSocket.cpp \
				ServerRun.cpp \
				Client.cpp \
				ServerUtils.cpp \
				Parsing.cpp \
				Commands/Bot_bonus.cpp \
				Commands/CmdsErrors.cpp \
				Commands/Invite.cpp \
				Commands/Join.cpp \
				Commands/Kick.cpp \
				Commands/Mode.cpp \
				Commands/Nick.cpp \
				Commands/Pass.cpp \
				Commands/Privmsg.cpp \
				Commands/Quit.cpp \
				Commands/cmdTopic.cpp \
				SplitString.cpp \
				Commands/User.cpp \
				Channel.cpp \
				ChannelRules.cpp \
				Topic.cpp

M_OBJECTS	:= $(addprefix $(DIR_OBJS_M), $(M_SOURCES:.cpp=.o))

INCLUDES	:= -Iincludes

TPUT  := tput -T xterm-256color
RESET := $(shell $(TPUT) sgr0)
GREEN := $(shell printf '\033[38;5;10m')
BLUE  := $(shell printf '\033[38;5;81m')

M_TOTAL		:= $(words $(M_SOURCES))
M_COUNT		:= 0

all: $(NAME)

$(DIR_OBJS_M)%.o: $(DIR_SRCS_M)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@$(eval M_COUNT=$(shell echo $$(( $(M_COUNT) + 1 ))))
	@printf "$(GREEN)(%3d%%)$(RESET) compiling $(BLUE)%s$(RESET)\n" \
	$$(( $(M_COUNT) * 100 / $(M_TOTAL) )) $<

$(NAME): $(M_OBJECTS)
	@$(CC) $(CFLAGS) $(M_OBJECTS) -o $(NAME)
	@printf "$(GREEN)$(NAME) created successfully ✔$(RESET)\n"

clean:
	@rm -rf objs
	@printf "$(GREEN)Objects cleaned ✔$(RESET)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(GREEN)Executables cleaned ✔$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re


