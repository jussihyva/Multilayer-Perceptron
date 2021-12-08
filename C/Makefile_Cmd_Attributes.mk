# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Cmd_Attributes.mk                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:03:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/12/08 17:03:32 by jkauppi          ###   ########.fr        #
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
	EPOCS			=	-E 100
endif

ifdef A
	LEARNING_RATE	=	-A $(A)
else
	LEARNING_RATE	=	-A 0.5
endif
