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

print('Hello World!')

from sklearn.model_selection import train_test_split

x = np.array(df.text)
y = np.array(df.label)
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.25)

clf = ak.TextClassifier()

clf.fit(x_train, y_train, epochs = 10)

print('Hello World!')

from sklearn.metrics import classification_report

y_hat = clf.predict(x_test)

print(classification_report(y_test, y_hat))

print('Hello World!')