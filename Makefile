# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/30 14:16:32 by majdahim          #+#    #+#              #
#    Updated: 2022/06/30 14:19:08 by majdahim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Webserv

all: $(NAME)

$(NAME) :
	c++  -std=c++98 *.cpp pars_config/server.cpp -o $(NAME)

re: fclean $(NAME)

clean:
	rm -f Webserv

fclean: clean

.PHONY: all re clean fclean%