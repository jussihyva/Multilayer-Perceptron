# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/07 14:28:42 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/07 18:02:53 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	ft_radian.c ft_max_int.c ft_min_int.c \
					ft_mod_int.c ft_mod_double.c \
					ft_matrix_x_vector_double.c \
					ft_max_double.c ft_min_double.c ft_isdigit_base.c \
					ft_strtoi.c ft_event_logging_1.c ft_event_logging_2.c \
					ft_event_logging_3.c ft_event_logging_4.c \
					ft_event_logging_5.c ft_event_logging_init.c \
					ft_event_logging_release.c \
					ft_openssl_init_ctx.c ft_openssl_init_client.c \
					ft_openssl_init.c ft_openssl_connect.c \
					ft_openssl_rel_conn.c ft_stack_push.c ft_stack_pop.c \
					ft_enqueue.c ft_dequeue.c ft_is_queue_empty.c \
					ft_queue_init.c \
					ft_bt_instert.c ft_bt_print.c ft_bt_find.c ft_bt_remove.c \
					ft_prio_enqueue.c ft_prio_dequeue.c ft_print_memory.c \
					ft_open_fd.c ft_arg_parser.c ft_print_leaks.c \
					ft_strarraydel.c ft_influxdb_connect.c ft_file_create.c \
					ft_home_dir.c ft_influxdb_write.c
SRC_H_FILES		=	libft_addons.h libft_addons_against_norm.h
