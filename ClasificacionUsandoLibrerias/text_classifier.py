#!/usr/bin/env python3

import pandas as pd
import numpy as np
import tensorflow as tf
import autokeras as ak

fileName = 'COV_train.txt'
df = pd.DataFrame({'label':int(), 'text':str()}, index=[])
with open(fileName) as f:
  for line in f.readlines():
    split = line.split('\t')
    df = df.append({'label': 1 if split[0]=='Positive' else 0,
                    'text': split[1]},
                   ignore_index = True)
df.head()

print('Carga de Datos Completada!')

from sklearn.model_selection import train_test_split

x = np.array(df.text)
y = np.array(df.label)
print(x.shape, y.shape)
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.01)
print(x_train.shape, x_test.shape, y_train.shape, y_test.shape)
clf = ak.TextClassifier(max_trials = 2)

clf.fit(x_train, y_train, epochs = 20)

print('Entrenamiento terminado!')

from sklearn.metrics import classification_report

y_hat = clf.predict(x_train)

print(classification_report(y_train, y_hat))

print('Clasificación Terminada!')