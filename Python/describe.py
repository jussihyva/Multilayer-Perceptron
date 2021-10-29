# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    describe.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:45:44 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/28 19:19:53 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import math
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pandas.core import indexing

class MyDescribe():
	def __init__(self):
		self.interpolation = "lower"

	def __calculate_percentile(self, dataset_fd, quantile, validate, columnNames):
		name = str(int(quantile * 100)) + "%"
		value_list = []
		if self.interpolation == "lower":
			for columnName in columnNames:
				value_list_sorted = (dataset_fd[columnName].dropna()).sort_values()
				value_list_sorted = value_list_sorted.reset_index(drop=True)
				numOfValues = len(value_list_sorted)
				rankValuePrel = int(numOfValues * int(quantile * 100))
				rankValue = int((rankValuePrel + 50) / 100)
				if (numOfValues % 2) == 1:
					if int(rankValuePrel / 100) == rankValue:
						value = value_list_sorted[rankValue]
					else:
						value = value_list_sorted[rankValue - 1]
				else:
					value = value_list_sorted[rankValue - 1]
				value_list.append(value)
			value_series = pd.Series(value_list, index=columnNames)
			if validate:
				self.describeValidator.percentile(dataset_fd, value_series, quantile, name)
		return ({name: value_list})

	def __calculate_max(self, dataset_fd, validate, columnNames):
		name = "Max"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataset_fd[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			value = value_list_sorted[numOfValues - 1]
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.max(dataset_fd, value_series, name)
		return ({name: value_list})

	def __calculate_min(self, dataset_fd, validate, columnNames):
		name = "Min"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataset_fd[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			value = value_list_sorted[0]
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.min(dataset_fd, value_series, name)
		return ({name: value_list})

	def __calculate_count(self, dataset_fd, validate, columnNames):
		name = "Count"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataset_fd[columnName].dropna())
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			value = numOfValues
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.count(dataset_fd, value_series, name)
		return ({name: value_list})

	def __calculate_median(self, dataset_fd, validate, columnNames):
		name = "Median"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataset_fd[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			rankValuePrel = int(numOfValues * 50)
			rankValue = int((rankValuePrel + 50) / 100)
			if (numOfValues % 2) == 0:
				value = (value_list_sorted[rankValue] + value_list_sorted[rankValue - 1]) / 2
			else:
				value = value_list_sorted[rankValue - 1]
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.median(dataset_fd, value_series, name)
		return ({name: value_list})

	def __sum(self, valueList):
		sum = 0
		for value in valueList:
			sum += value
		return (sum)

	def __variance(self, valueList, mean, std2):
		sum = 0
		for value in valueList:
			sum += pow((value - mean), 2)
		if std2 == True:
			variance = sum / (len(valueList) - 1)
		else:
			variance = sum / len(valueList)
		return (variance)

	def __calculate_mean(self, dataset_fd, validate, columnNames):
		name = "Mean"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataset_fd[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			sum = self.__sum(value_list_sorted)
			numOfValues = len(value_list_sorted)
			value = sum / numOfValues
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.mean(dataset_fd, value_series, name)
		return ({name: value_list})

	def __calculate_std(self, dataset_fd, validate, std2, columnNames):
		name = "Std"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataset_fd[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			sum = self.__sum(value_list_sorted)
			numOfValues = len(value_list_sorted)
			variance = self.__variance(value_list_sorted, sum / numOfValues, std2)
			value = math.sqrt(variance)
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.std(dataset_fd, value_series, name)
		return ({name: value_list})

	def createDescribeDataFrame(self, dataset_fd, validate, std2, columnNames):
		describe_list = {}
		describe_list.update(self.__calculate_count(dataset_fd, validate, columnNames))
		describe_list.update(self.__calculate_mean(dataset_fd, validate, columnNames))
		describe_list.update(self.__calculate_std(dataset_fd, validate, std2, columnNames))
		describe_list.update(self.__calculate_median(dataset_fd, validate, columnNames))
		describe_list.update(self.__calculate_min(dataset_fd, validate, columnNames))
		describe_list.update(self.__calculate_max(dataset_fd, validate, columnNames))
		for quantile in [0.01, 0.25, 0.50, 0.75, 0.99]:
			describe_list.update(self.__calculate_percentile(dataset_fd, quantile, validate, columnNames))
		return (describe_list)
