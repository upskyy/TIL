from keras.models import Sequential
from keras.layers.core import Dense
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import StratifiedKFold

import numpy
import pandas as pd
import tensorflow as tf

seed = 0
numpy.random.seed(seed)
tf.random.set_seed(3)

df = pd.read_csv('../deeplearning/dataset/sonar.csv')

dataset = df.values
X = dataset[:,0:-1].astype(float)
Y_obj = dataset[:,-1]

e = LabelEncoder()
e.fit(Y_obj)
Y = e.transform(Y_obj)

n_fold = 10
skf = StratifiedKFold(n_splits=n_fold, shuffle=True, random_state=seed)

total_accuracy = []

for train, test in skf.split(X, Y):
    model = Sequential()
    model.add(Dense(24, input_dim=60, activation='relu'))
    model.add(Dense(10, activation='relu'))
    model.add(Dense(1, activation='sigmoid'))
    model.compile(loss='mean_squared_error',
                  optimizer='adam',
                  metrics=['accuracy'])
    model.fit(X[train], Y[train], epochs=100, batch_size=5)
    accuracy = "%.4f" % (model.evaluate(X[test], Y[test])[1])
    total_accuracy.append(accuracy)

print("\n %.f fold accuracy:" % n_fold, total_accuracy)