# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Cmd_Attributes.mk                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:03:48 by jkauppi           #+#    #+#              #
#    Updated: 2022/07/11 12:18:30 by jkauppi          ###   ########.fr        #
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

ifdef E
	EPOCS			=	-E $(E)
else
	EPOCS			=	-E 10000
endif

ifdef A
	LEARNING_RATE	=	-A $(A)
else
	LEARNING_RATE	=	-A 0.04
endif
