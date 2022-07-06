# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 16:31:11 by jkauppi           #+#    #+#              #
#    Updated: 2022/07/03 16:46:29 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all build start login stop remove create_keys print_key clean fclean

OS				=	$(shell uname -s)
ifeq ($(OS), Darwin)
	DOCKER_COMPOSE	=	docker-compose
else
	DOCKER_COMPOSE	=	docker-compose
endif

# Colours for printouts
RED					=	\033[0;31m
GREEN				=	\033[0;32m
YELLOW				=	\033[0;33m
GRAY				=	\033[1;30m
PURPLE				=	\033[0;35m
END					=	\033[0m

SELF_SIGNED_CRT	=	./jupyter-selfsigned.crt
SELF_SIGNED_KEY	=	./jupyter-selfsigned.key

all: start

build: $(SELF_SIGNED_CRT)
	$(DOCKER_COMPOSE) build

start: build
	$(DOCKER_COMPOSE) up -d
	@echo "$(GREEN)Docker for jupyter started!$(PURPLE) Login to jupyter: http://localhost:8000 (password=Hive42)$(END)"

login_jupyter:
	docker exec -it jupyter bash

login_grafana:
	docker exec -it grafana bash

login_chronograf:
	docker exec -it chronograf bash

stop:
	-docker kill jupyter
	@echo "$(GREEN)Docker for jupyter stopped!$(END)"

remove: stop
	-docker rm jupyter
	@echo "$(GREEN)Docker for jupyter removed!$(END)"

$(SELF_SIGNED_CRT):
	@openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=Hive/CN=jupyter" 2>/dev/null
	@chmod 644 $(SELF_SIGNED_CRT)
	@chmod +r $(SELF_SIGNED_KEY)
	@echo "Self signed cert $(GREEN)$(SELF_SIGNED_CRT)$(END) created!"

clean: remove

fclean: clean
	@-\rm $(SELF_SIGNED_CRT)
	@-\rm $(SELF_SIGNED_KEY)
	@echo "Self signed cert $(GREEN)$(SELF_SIGNED_CRT)$(END) removed!"
