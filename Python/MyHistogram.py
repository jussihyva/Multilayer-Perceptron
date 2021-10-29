# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MyHistogram.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 14:40:42 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/29 17:32:46 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

class MyHistogram():
	def __init__(self):
		pass

	def histogram(self, dataFrame, columnList, axes, legends):
		axes = axes.flatten()
		for i in range(0, len(columnList)):
			for legend in legends:
				legendIndexList = dataFrame.where(dataFrame["Diagnosis"] == legend).dropna().index
				axes[i].hist(dataFrame[columnList[i]][legendIndexList],
				alpha=0.3)
			axes[i].set_title(columnList[i], fontsize=30)
			axes[i].legend(legends, fontsize=10)
