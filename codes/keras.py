# import necessary modules
from keras.models import Sequential
from keras.layers import Dense
import numpy


# load input data
dataset = numpy.loadtxt("input_data.csv", delimiter=",")


# split into input variables (X) and output variables (Y)
X = dataset[:,0:8]
Y = dataset[:,8]

# choose the model
model = Sequential()
#add a layer of 12 neurons that expects 8 input variables (as many as the input data)
model.add(Dense(12, input_dim=8, activation='relu'))
#add a layer of 8 neurons (it expexts as input variables as many neurons as the previous layer had)
model.add(Dense(8, activation='relu'))
#add the output layer with 1 ouptut variable
model.add(Dense(1, activation='sigmoid'))

# Compile the model
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

# Fit/train the model
model.fit(X, Y, epochs=150, batch_size=10)

# evaluate the model
scores = model.evaluate(X, Y)
print("\n%s: %.2f%%" % (model.metrics_names[1], scores[1]*100))