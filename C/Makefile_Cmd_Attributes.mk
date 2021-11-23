# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Cmd_Attributes.mk                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:03:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/23 12:44:16 by juhani           ###   ########.fr        #
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
	EPOCS		=	-E $(E)
else
	EPOCS		=	-E 1000
endif
