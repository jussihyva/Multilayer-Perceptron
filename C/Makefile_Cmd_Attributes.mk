# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Cmd_Attributes.mk                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:03:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/03 11:05:32 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef D
	DATASET			=	$(D)
else
	DATASET			=	"../Data/data.csv"
endif

ifdef L
	LEVEL			=	-L $(L)
else
	LEVEL			=
endif

ifdef M
	MODE			=	$(M)
else
	MODE			=	TRAIN
endif

ifdef I
	ITERATIONS		=	-I $(I)
else
	ITERATIONS		=	-I 10000
endif
