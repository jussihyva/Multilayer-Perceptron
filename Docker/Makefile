# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 16:31:11 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/15 17:00:08 by jkauppi          ###   ########.fr        #
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

SELF_SIGNED_CRT	=	./influxdb-selfsigned.crt
SELF_SIGNED_KEY	=	./influxdb-selfsigned.key

all: start

build: $(SELF_SIGNED_CRT)
	$(DOCKER_COMPOSE) build

start: build
	$(DOCKER_COMPOSE) up -d
	@echo "$(GREEN)Docker for influxdb/grafana started!$(PURPLE) Login to grafana: https://localhost:8086 (UserID/PW = admin/admin)$(END)"

login_influxdb:
	docker exec -it influxdb bash
	# influx  -ssl -unsafeSsl
	# create database Hive

login_grafana:
	docker exec -it grafana bash

login_chronograf:
	docker exec -it chronograf bash

stop:
	-docker kill chronograf
	-docker kill grafana
	-docker kill influxdb
	@echo "$(GREEN)Docker for influxdb stopped!$(END)"

remove: stop
	-docker rm chronograf
	-docker rm grafana
	-docker rm influxdb
	@echo "$(GREEN)Docker for influxdb removed!$(END)"

$(SELF_SIGNED_CRT):
	@openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=Hive/CN=influxdb" 2>/dev/null
	@chmod 644 $(SELF_SIGNED_CRT)
	@chmod +r $(SELF_SIGNED_KEY)
	@echo "Self signed cert $(GREEN)$(SELF_SIGNED_CRT)$(END) created!"

clean: remove

fclean: clean
	@-\rm $(SELF_SIGNED_CRT)
	@-\rm $(SELF_SIGNED_KEY)
	@echo "Self signed cert $(GREEN)$(SELF_SIGNED_CRT)$(END) removed!"
