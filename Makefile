# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/27 10:15:40 by brturcio          #+#    #+#              #
#    Updated: 2026/02/27 11:58:02 by brturcio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME        := ircserv
# CC          := c++
# CFLAGS      := -Wall -Wextra -Werror -std=c++98
#
# DIR_SRCS    := sources/
# DIR_OBJS    := objs/
#
# SOURCES     := main.cpp
# OBJECTS     := $(addprefix $(DIR_OBJS), $(SOURCES:.cpp=.o))
#
# INCLUDES    := -Iincludes
#
# GREEN       := \033[0;32m
# RESET       := \033[0m
#
# TOTAL       := $(words $(SOURCES))
# COUNT       := 0
#
# all: $(NAME)
#
# $(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
# 	@mkdir -p $(DIR_OBJS)
# 	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# 	@$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
# 	@printf "$(GREEN)[%d%%]$(RESET) Compiling %s\n" $$(( $(COUNT) * 100 / $(TOTAL) )) $<
#
# $(NAME): $(OBJECTS)
# 	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
# 	@echo "$(GREEN)✔ $(NAME) Created Successfully!$(RESET)"
#
# clean:
# 	@rm -rf $(DIR_OBJS)
# 	@echo "$(GREEN)✔ Objects Cleaned$(RESET)"
#
# fclean: clean
# 	@rm -rf $(NAME)
# 	@echo "$(GREEN)✔ Executable Cleaned$(RESET)"
#
# re: fclean all
#
# .PHONY: all clean fclean re


NAME        := ircserv
CC          := c++
CFLAGS      := -Wall -Wextra -Werror -std=c++98

DIR_SRCS    := sources/
DIR_OBJS    := objs/

SOURCES     := main.cpp
OBJECTS     := $(addprefix $(DIR_OBJS), $(SOURCES:.cpp=.o))

INCLUDES    := -Iincludes

TPUT    := tput -T xterm-256color
_RESET  := $(shell $(TPUT) sgr0)
_BOLD   := $(shell $(TPUT) bold)
_GREEN  := $(shell $(TPUT) setaf 2)
_PURPLE := $(shell $(TPUT) setaf 5)

TOTAL   := $(words $(SOURCES))
COUNT   := 0

all: $(NAME)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
	@mkdir -p $(DIR_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	@printf "$(_GREEN)($(_BOLD)%3d%%$(_RESET)$(_GREEN)) $(_RESET)compiling $(_BOLD)$(_PURPLE)%s$(_RESET)\n" \
	$$(( $(COUNT) * 100 / $(TOTAL) )) $<

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(_BOLD)$(NAME)$(_RESET) created $(_GREEN)$(_BOLD)successfully ✔$(_RESET)\n"

clean:
	@rm -rf $(DIR_OBJS)
	@printf "$(_BOLD)Objects$(_RESET) $(_GREEN)cleaned ✔$(_RESET)\n\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(_BOLD)$(NAME)$(_RESET) $(_GREEN)cleaned ✔$(_RESET)\n\n"

re: fclean all

.PHONY: all clean fclean re


