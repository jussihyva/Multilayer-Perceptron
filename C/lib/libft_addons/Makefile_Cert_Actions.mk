# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_cert_actions.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/07 16:26:16 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/07 16:27:50 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(SELF_SIGNED_CRT):
	openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=Hive/CN=n-puzzle"
	chmod 644 $(SELF_SIGNED_CRT)
	chmod +r $(SELF_SIGNED_KEY)
