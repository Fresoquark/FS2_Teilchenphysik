import numpy as np
from sklearn.model_selection import train_test_split
import pandas as pd
from scipy.spatial import distance
from sklearn.metrics.cluster import v_measure_score
from sklearn.metrics import accuracy_score

class KNN:
    '''KNN Classifier.

    Attributes
    ----------
    k : int
        Number of neighbors to consider.
    '''
    def __init__(self, k):
        '''Initialization.
        Parameters are stored as member variables/attributes.

        Parameters
        ----------
        k : int
            Number of neighbors to consider.
        '''
        self.k = k


    def euc(self, a, b):
        return distance.euclidean(a, b)


    def fit(self, X_train, y_train):
        '''Fit routine.
        Training data is stored within object.

        Parameters
        ----------
        X : numpy.array, shape=(n_samples, n_attributes)
            Training data.
        y : numpy.array shape=(n_samples)
            Training labels.
        '''
        # Code
        self.X_train = X_train
        self.y_train = y_train

    def predict(self, X):
        '''Prediction routine.
        Predict class association of each sample of X.

        Parameters
        ----------
        X : numpy.array, shape=(n_samples, n_attributes)
            Data to classify.

        Returns
        -------
        prediction : numpy.array, shape=(n_samples)
            Predictions, containing the predicted label of each sample.
        '''
        # Code
        pred = []
        # row_count = 0
        for row in X: # iteriere durch jedes event
            # label = orte mit kleinstem abstand
            label = self.closest_points(row, self.X_train)
            # pred.append(prediction)
            N_sig = 0
            N_bg = 0
            for i in label:
                if self.y_train[i] == 0:
                    N_sig += 1
                else:
                    N_bg += 1
            if N_sig >= N_bg: # wenn label = signal ist dann 0 ( weil 0 = signal heisst)
                pred.append(0)
            else:
                pred.append(1) # sonst 1 appenden da 1 = bg
            # if row_count % 10000 == 0:
                # print(row_count)
            # row_count += 1
        return pred

    # # hier muss ich noch schauen wie wir an die trainingsdaten kommen.
    # # andere idee: das was in der aufgabe_1.py steht klatschen wir infach hier drunter dann ist es einfach
    def closest_points(self, row, X):
        index = [] # speichere hier die besten indizes
        distances = [] # alle distanzen
        distances = distance.cdist([row], X, 'euclidean')
        # for i in range(1, len(X)):
        #     dist = self.euc(X[i], row) # bestimme alle abstaende jedes testevents zu jedem trainingsevent
        #     distances.append(dist)
        sort_dist = np.argsort(distances) # sortiere die distancen und gibt die k kleinsten zurueck
        for j in range(self.k):
            index.append(sort_dist[0][j])

        return index


data = pd.read_hdf('~/Downloads/NeutrinoMC.hdf5', key='Signal')
Background = pd.read_hdf('~/Downloads/NeutrinoMC.hdf5', key='Background')
# label: 0 = signal, 1 = BG
y_sig = pd.DataFrame(data={'label':np.zeros(data['x'].shape[0])})
y_bg = pd.DataFrame(data={'label':np.ones(Background['x'].shape[0])})

our_data = {'NumberOfHits':data['NumberOfHits'], 'x':data['x'], 'y':data['y']}
our_BG = {'NumberOfHits':Background['NumberOfHits'], 'x':Background['x'], 'y':Background['y']}

X_sig = pd.DataFrame(data=our_data)
X_bg = pd.DataFrame(data=our_BG)
# fertige datensaetze
signal = pd.concat([X_sig, y_sig], axis=1)
bg = pd.concat([X_bg, y_bg], axis=1)

signal = np.nan_to_num(signal)
signal = signal[~np.all(signal == 0, axis = 1)]

bg = np.array(bg)
bg = bg[:25000, :]

signal = signal[:15000, :]
gesamt = np.concatenate((signal, bg), axis=0)

X = gesamt[:, :-1]
y = gesamt[:, -1]


K_num = [10, 20]
a = [0, 1]
for j in K_num:
    print('k = ', j)
    for num in a:
        if num == 0:
            print("normal")
            X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.75, random_state=42)
        else:
            print("log10")
            X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.75, random_state=42)
            X_train[:, 0] = np.log10(X_train[:, 0])
            X_test[:, 0] = np.log10(X_test[:, 0])
        our_KNN = KNN(j) # init
        our_KNN.fit(X_train, y_train) # trainieren
        PRED = our_KNN.predict(X_test) # labels predicten
        # efficiency Eff, purity P and significance S
        tp = 0
        fp = 0
        fn = 0
        tn = 0
        for i in range(len(y_test)):
            if PRED[i] == y_test[i] and PRED[i] == 0:
                tp += 1
            if PRED[i] == 0 and y_test[i] == 1:
                fp += 1
            if PRED[i] == 1 and y_test[i] == 0:
                fn += 1
            if PRED[i] == y_test[i] and PRED[i] == 1:
                tn += 1

        print('tp: ', tp, 'fp: ', fp, 'fn: ', fn, 'tn:', tn)

        Eff = tp / (tp + fn)
        P = tp / (tp + fp)
        S = tp / np.sqrt(tp + tn)
        accuracy = (tp + tn) / (tp + fp + tn + fn)

        print('v score: purity = ', v_measure_score(PRED, y_test))
        print('accuracy score(sklearn) = ', accuracy_score(PRED, y_test))

        print('Eff: ', Eff)
        print('Purity: ', P)
        print('Signifikanz: ', S)
        print('Accuracy: ', accuracy)
        print('################################')
