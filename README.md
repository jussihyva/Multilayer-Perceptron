# Multilayer-Perceptron

```diff
- The project is still ongoing. I do daily updates into the contents.
```

## 1. Project overview

The project is part of my studying at [Hive (Helsinki) Coding School](https://hive.fi). Programs are written in C-, and python- languages. An additional visualization (Bonus part of the project) I used Influxdb and Grafana which are running inside a docker container. For visualization I used Jupyter notebook. The picture below visualizes a general overview of a curriculum (Holy Graph) and my progress at Hive Coding School.

![Hive_Holy_Graph](Documentation/Hive_Holy_Graph.png)

## 2. Project description

**Note.** Text into this chapter (project description) was copied (partly or fully) from Hive Coding School document.

### 2.1 Introduction

In the language of your choice you are going to implement a multilayer perceptron, in order to predict whether a cancer is malignant or benign on a dataset of breast cancer diagnosis in the Wisconsin.

### 2.2 Mandatory part

#### 2.2.1 Foreword

A non-negligible part of the evaluation will be based on your understanding of the training phase (also called the learning phase) and the underlying algorithms. You will be asked to explain to your corrector the notions of feedforward, backpropagation and gradient descent. Points will be attributed depending on the clarity of your explanations. These notions are important for the next projects of the branch and will represent a real asset if you wish to continue in this field.

#### 2.2.2 Dataset

The dataset is provided in the resources. It is a csv file of 32 columns, the column diagnosis being the label you want to learn given all the other features of an example, it can be either the value M or B (for malignant or benign). The features of the dataset describe the characteristics of a cell nucleus of breast mass extracted with [fine-needle aspiration](https://en.wikipedia.org/wiki/Fine-needle_aspiration). (for more detailed informations, go [here](https://archive.ics.uci.edu/ml/machine-learning-databases/breast-cancer-wisconsin/wdbc.names)). As you will see, there is an important work of data understanding before starting to implement the algorithm which will be able to classify it. A good practice would be to begin by playing with the dataset by displaying it with graphs, visualizing and manipulating its different features.

#### 2.2.3 Implementation

Your implementation of the neural network must contain at least two hidden layers (the idea is to make you write a program a bit more modular. Although this won’t be graded, it still is a good habit to take). You must also implement the softmax function on the output layer in order to obtain the output as a probabilistic distribution. In order to evaluate the performances of your model in a robust way during training, you will split your dataset in two parts, one for the training, and one for the validation (the validation dataset is used to determine the accuracy of your model on unknown examples).
To visualize your model performances during training, you will display at each epoch
the training and validation metrics, for example :

```text
    epoch 39/70 - loss: 0.0750 - val_loss: 0.0406
    epoch 40/70 - loss: 0.0749 - val_loss: 0.0404
    epoch 41/70 - loss: 0.0747 - val_loss: 0.0403
```

You will also implement a learning curve graph displayed at the end of the training phase (you are free to use any library you want for this purpose).

#### 2.2.4 Submission

You will submit two programs, the first for the training phase, and the second for the prediction phase (or you can submit a single program with an option to switch between the two phases) :
• The training program will use backpropagation and gradient descent to learn on the training dataset and will save the model (network topology and weights) at the end of its execution.
• The prediction program will load the weights learned in the previous phase, perform a prediction on a given set (which will also be loaded), then evaluate it using the binary [cross-entropy error function](https://en.wikipedia.org/wiki/Cross_entropy#Cross-entropy_error_function_and_logistic_regression):

![g](https://latex.codecogs.com/svg.latex?\Large&space;E=-\frac{1}{N}\sum_{n=1}^{N}[y_{n}log(p_{n})+(1-y_{n})log(1-p_{n})])

#### 2.2.5 Input file

ID number|Diagnosis|Mean Radius|Mean Texture|Mean Perimeter|Mean Area|Mean Smoothness|Mean Compactness|Mean Concavity|Mean Concave points|Mean Symmetry|Mean Fractal dimension|Radius SE|Texture SE|Perimeter SE|Area SE|Smoothness SE|Compactness SE|Concavity SE|Concave points SE|Symmetry SE|Fractal dimension SE|Worst Radius|Worst Texture|Worst Perimeter|Worst Area|Worst Smoothness|Worst Compactness|Worst Concavity|Worst Concave points|Worst Symmetry|Worst Fractal dimension|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
842302|M|17.99|10.38|122.8|1001|0.1184|0.2776|0.3001|0.1471|0.2419|0.07871|1.095|0.9053|8.589|153.4|0.006399|0.04904|0.05373|0.01587|0.03003|0.006193|25.38|17.33|184.6|2019|0.1622|0.6656|0.7119|0.2654|0.4601|0.1189|
842517|M|20.57|17.77|132.9|1326|0.08474|0.07864|0.0869|0.07017|0.1812|0.05667|0.5435|0.7339|3.398|74.08|0.005225|0.01308|0.0186|0.0134|0.01389|0.003532|24.99|23.41|158.8|1956|0.1238|0.1866|0.2416|0.186|0.275|0.08902|
84300903|M|19.69|21.25|130|1203|0.1096|0.1599|0.1974|0.1279|0.2069|0.05999|0.7456|0.7869|4.585|94.03|0.00615|0.04006|0.03832|0.02058|0.0225|0.004571|23.57|25.53|152.5|1709|0.1444|0.4245|0.4504|0.243|0.3613|0.08758|
|:|
926954|M|16.6|28.08|108.3|858.1|0.08455|0.1023|0.09251|0.05302|0.159|0.05648|0.4564|1.075|3.425|48.55|0.005903|0.03731|0.0473|0.01557|0.01318|0.003892|18.98|34.12|126.7|1124|0.1139|0.3094|0.3403|0.1418|0.2218|0.0782|
927241|M|20.6|29.33|140.1|1265|0.1178|0.277|0.3514|0.152|0.2397|0.07016|0.726|1.595|5.772|86.22|0.006522|0.06158|0.07117|0.01664|0.02324|0.006185|25.74|39.42|184.6|1821|0.165|0.8681|0.9387|0.265|0.4087|0.124|
92751|B|7.76|24.54|47.92|181|0.05263|0.04362|0|0|0.1587|0.05884|0.3857|1.428|2.548|19.15|0.007189|0.00466|0|0|0.02676|0.002783|9.456|30.37|59.16|268.6|0.08996|0.06444|0|0|0.2871|0.07039|

## 3. Solution

## 3.1 Exploratory data analysis

The aim of this chapter is to give an overview of the dataset content

## 3.1.1 Aggregate functions

Based on the result I did these observations:

- The Count function shows that the examples (rows in the dataset) includes data for all columns
- Mode functio is missing from the list. I think that is not big issue. That because of all columns includes values so no reason to add any missing values.
- Fo some reason (maybe a lack of competence) I cannot sey much more about these numbers

![Aggregate functions](Documentation/Aggregate_functions.png)

## 3.1.2 Histogram

Six of the mean gauges (Radius, Perimeter, Area, Compactness, Concavity and Concave points) separate cancer types very well. The rest four are overlapping. So, maybe only six gauges could be used as input for a machine-learning model. Error gauges are overlapping much more. I don't have experience with cancer-related medical details, I cannot make a decision on how important error gauges are analysis point of view. Worst-gauges behave similarly to mean gauges. So, maybe the usage of mean gauges gives a good enough result to predict a type of cancer.
So, based on Histogram visualization, I think that mean gauge values are enough for valid cancer type prediction.

![Histogram mean](Documentation/Histogram_mean.png)

![Histogram SE](Documentation/Histogram_SE.png)

![Histogram worst](Documentation/Histogram_worst.png)

## 3.1.3 Scatter matrix

There are three gauges (Radius, Perimeter and Area) that correlate very well with each other, so maybe just one of them is enough to be used for cancer type prediction.

![Histogram mean](Documentation/Scatter_matrix_mean.png)

![Histogram SE](Documentation/Scatter_matrix_SE.png)

![Histogram worst](Documentation/Scatter_matrix_worst.png)

## 3.1.4 Box

All gauges have some values that are out of the box (nice sentence). So, maybe those measurement results should be removed. I have to check (I don't know yet how to do that professionally) are those measurements invalid with all gauge values or just randomly one faulty result here and there.

![Histogram mean](Documentation/Box_mean.png)

![Histogram SE](Documentation/Box_SE.png)

![Histogram worst](Documentation/Box_worst.png)

## 3.1.5 Correlation

The correlation pictures indicate similar things to Scatter matrix pictures. So, there is nothing additional information from these pictures.

![Histogram mean](Documentation/Correlation_mean.png)

![Histogram SE](Documentation/Correlation_SE.png)

![Histogram worst](Documentation/Correlation_worst.png)
