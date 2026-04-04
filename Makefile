# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntome <ntome@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/27 10:15:40 by brturcio          #+#    #+#              #
#    Updated: 2026/04/03 21:24:12 by brturcio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= ircserv
BONUS		:= ircserv_bonus
CC			:= c++
CFLAGS		:= -Wall -Wextra -Werror -std=c++98 -g

DIR_SRCS_M	:= sources/mandatory/
DIR_SRCS_B	:= sources/bonus/

DIR_OBJS_M	:= objs/mandatory/
DIR_OBJS_B	:= objs/bonus/

M_SOURCES	:=  main.cpp \
				Server.cpp \
				ServerSocket.cpp \
				ServerRun.cpp \
				Client.cpp \
				ServerUtils.cpp \
				Parsing.cpp \
				Commands/CmdsErrors.cpp \
				Commands/Invite.cpp \
				Commands/Join.cpp \
				Commands/Kick.cpp \
				Commands/Mode.cpp \
				Commands/Nick.cpp \
				Commands/Pass.cpp \
				Commands/Privmsg.cpp \
				Commands/Quit.cpp \
				SplitString.cpp \
				Commands/User.cpp \
				Channel.cpp \
				ChannelRules.cpp \
				Topic.cpp
B_SOURCES	:= 

M_OBJECTS	:= $(addprefix $(DIR_OBJS_M), $(M_SOURCES:.cpp=.o))
B_OBJECTS	:= $(addprefix $(DIR_OBJS_B), $(B_SOURCES:.cpp=.o))

INCLUDES	:= -Iincludes

TPUT  := tput -T xterm-256color
RESET := $(shell $(TPUT) sgr0)
GREEN := $(shell printf '\033[38;5;10m')
BLUE  := $(shell printf '\033[38;5;81m')

M_TOTAL		:= $(words $(M_SOURCES))
M_COUNT		:= 0
B_TOTAL		:= $(words $(B_SOURCES))
B_COUNT		:= 0

all: $(NAME)

bonus: $(BONUS)

$(DIR_OBJS_M)%.o: $(DIR_SRCS_M)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@$(eval M_COUNT=$(shell echo $$(( $(M_COUNT) + 1 ))))
	@printf "$(GREEN)(%3d%%)$(RESET) compiling $(BLUE)%s$(RESET)\n" \
	$$(( $(M_COUNT) * 100 / $(M_TOTAL) )) $<

$(DIR_OBJS_B)%.o: $(DIR_SRCS_B)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@$(eval B_COUNT=$(shell echo $$(( $(B_COUNT) + 1 ))))
	@printf "$(GREEN)(%3d%%)$(RESET) compiling $(BLUE)%s$(RESET)\n" \
	$$(( $(B_COUNT) * 100 / $(B_TOTAL) )) $<

$(NAME): $(M_OBJECTS)
	@$(CC) $(CFLAGS) $(M_OBJECTS) -o $(NAME)
	@printf "$(GREEN)$(NAME) created successfully ✔$(RESET)\n"

$(BONUS): $(B_OBJECTS)
	@$(CC) $(CFLAGS) $(B_OBJECTS) -o $(BONUS)
	@printf "$(GREEN)$(BONUS) created successfully ✔$(RESET)\n"

clean:
	@rm -rf objs
	@printf "$(GREEN)Objects cleaned ✔$(RESET)\n"

fclean: clean
	@rm -rf $(NAME) $(BONUS)
	@printf "$(GREEN)Executables cleaned ✔$(RESET)\n"

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus


