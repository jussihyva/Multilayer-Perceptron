# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MyDescribe.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:45:44 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/01 15:19:51 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import math
import pandas as pd

class MyDescribe():
	def __init__(self):
		self.interpolation = "lower"

	def __calculate_percentile(self, dataFrame, quantile, validate, columnNames):
		name = str(int(quantile * 100)) + "%"
		value_list = []
		if self.interpolation == "lower":
			for columnName in columnNames:
				value_list_sorted = (dataFrame[columnName].dropna()).sort_values()
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
				self.describeValidator.percentile(dataFrame, value_series, quantile, name)
		return ({name: value_list})

	def __calculate_max(self, dataFrame, validate, columnNames):
		name = "Max"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataFrame[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			value = value_list_sorted[numOfValues - 1]
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.max(dataFrame, value_series, name)
		return ({name: value_list})

	def __calculate_min(self, dataFrame, validate, columnNames):
		name = "Min"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataFrame[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			value = value_list_sorted[0]
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.min(dataFrame, value_series, name)
		return ({name: value_list})

	def __calculate_count(self, dataFrame, validate, columnNames):
		name = "Count"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataFrame[columnName].dropna())
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			value = numOfValues
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.count(dataFrame, value_series, name)
		return ({name: value_list})

	def __calculate_median(self, dataFrame, validate, columnNames):
		name = "Median"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataFrame[columnName].dropna()).sort_values()
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
			self.describeValidator.median(dataFrame, value_series, name)
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

	def __calculate_mean(self, dataFrame, validate, columnNames):
		name = "Mean"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataFrame[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			sum = self.__sum(value_list_sorted)
			numOfValues = len(value_list_sorted)
			value = sum / numOfValues
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.mean(dataFrame, value_series, name)
		return ({name: value_list})

	def __calculate_std(self, dataFrame, validate, std2, columnNames):
		name = "Std"
		value_list = []
		for columnName in columnNames:
			value_list_sorted = (dataFrame[columnName].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			sum = self.__sum(value_list_sorted)
			numOfValues = len(value_list_sorted)
			variance = self.__variance(value_list_sorted, sum / numOfValues, std2)
			value = math.sqrt(variance)
			value_list.append(value)
		value_series = pd.Series(value_list, index=columnNames)
		if validate:
			self.describeValidator.std(dataFrame, value_series, name)
		return ({name: value_list})

	def createDescribeDataFrame(self, dataFrame, validate, std2, columnNames):
		describe_list = {}
		describe_list.update(self.__calculate_count(dataFrame, validate, columnNames))
		describe_list.update(self.__calculate_mean(dataFrame, validate, columnNames))
		describe_list.update(self.__calculate_std(dataFrame, validate, std2, columnNames))
		describe_list.update(self.__calculate_median(dataFrame, validate, columnNames))
		describe_list.update(self.__calculate_min(dataFrame, validate, columnNames))
		for quantile in [0.01, 0.25, 0.50, 0.75, 0.99]:
			describe_list.update(self.__calculate_percentile(dataFrame, quantile, validate, columnNames))
		describe_list.update(self.__calculate_max(dataFrame, validate, columnNames))
		return (describe_list)

if __name__ == "__main__":
	scriptDirectory = (os.path.dirname(os.path.realpath(__file__)))
	gaugeColumnList = {}
	gaugeColumnList["Mean"] = ["Mean Radius","Mean Texture","Mean Perimeter","Mean Area","Mean Smoothness","Mean Compactness","Mean Concavity","Mean Concave points","Mean Symmetry","Mean Fractal dimension"]
	gaugeColumnList["SE"] = ["Radius SE","Texture SE","Perimeter SE","Area SE","Smoothness SE","Compactness SE","Concavity SE","Concave points SE","Symmetry SE","Fractal dimension SE"]
	gaugeColumnList["Worst"] = ["Worst Radius","Worst Texture","Worst Perimeter","Worst Area","Worst Smoothness","Worst Compactness","Worst Concavity","Worst Concave points","Worst Symmetry","Worst Fractal dimension"]
	columnNames = []
	columnNames.extend(["ID number","Diagnosis"])
	columnNames.extend(gaugeColumnList["Mean"])
	columnNames.extend(gaugeColumnList["SE"])
	columnNames.extend(gaugeColumnList["Worst"])
	dataset_training = pd.read_csv(str(scriptDirectory) + "/../Data/data.csv", header=None, names=columnNames)
	myDescribe = MyDescribe()
	columnsTypeList = ["Mean", "SE", "Worst"]
	for columnsType in columnsTypeList:
		describe_list = myDescribe.createDescribeDataFrame(dataset_training, False, False, gaugeColumnList[columnsType])
		my_describe_df = pd.DataFrame(describe_list, index=gaugeColumnList[columnsType])
		print("Data type: " + str(columnsType))
		print(my_describe_df)
		print("")
