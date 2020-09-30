import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from sklearn.datasets import make_blobs
from sklearn.decomposition import PCA
import pandas as pd
from sklearn import (
    ensemble, linear_model, neighbors, svm, tree, naive_bayes,
    gaussian_process, neural_network, dummy)
from skfeature.function.information_theoretical_based import MRMR

model = ensemble.RandomForestRegressor(n_estimators=100)

discrete_cmap = ListedColormap([(0.8, 0.2, 0.3), (0.1, 0.8, 0.3), (0, 0.4, 0.8)])

signal = pd.read_csv("../signal.csv", sep = ";")
bkg = pd.read_csv("../background.csv", sep = ";")

signal = signal.drop(signal.filter(regex='MC').columns, axis=1)
signal = signal.drop(signal.filter(regex='Weight').columns, axis=1)
signal = signal.drop(signal.filter(regex='Corsika').columns, axis=1)
signal = signal.drop(signal.filter(regex='end').columns, axis=1)
signal = signal.drop(signal.filter(regex='start').columns, axis=1)
signal = signal.drop(signal.filter(regex='time').columns, axis=1)
signal = signal.drop('label', axis=1)

bkg = bkg.drop(bkg.filter(regex='MC').columns, axis=1)
bkg = bkg.drop(bkg.filter(regex='Weight').columns, axis=1)
bkg = bkg.drop(bkg.filter(regex='Corsika').columns, axis=1)
bkg = bkg.drop(bkg.filter(regex='end').columns, axis=1)
bkg = bkg.drop(bkg.filter(regex='start').columns, axis=1)
bkg = bkg.drop(bkg.filter(regex='time').columns, axis=1)
bkg = bkg.drop('label', axis=1)

signal.replace([np.inf, -np.inf], np.nan)
signal.dropna(axis = 'columns', inplace = True)
signal = signal.drop(signal.std()[(signal.std() == 0)].index, axis=1)

bkg.replace([np.inf, -np.inf], np.nan)
bkg.dropna(axis = 'columns', inplace = True)
bkg = bkg.drop(bkg.std()[(bkg.std() == 0)].index, axis=1)

bcol = bkg.columns
scol = signal.columns

for att in scol:
    if att not in bcol:
        signal.drop(att, axis=1, inplace = True)

for att in bcol:
    if att not in scol:
        bkg.drop(att, axis=1, inplace = True)

import scipy.io
from sklearn.metrics import accuracy_score
from sklearn.model_selection import cross_validate
from sklearn import svm

sig_label = np.zeros(signal.shape[0])
bkg_label = np.ones(bkg.shape[0])

combined_df = pd.concat([signal, bkg], ignore_index=True)
combined_label = np.append(sig_label, bkg_label)

combined_df.insert(118, 'label', combined_label)
shuffled = combined_df.sample(frac = 1)

y = shuffled['label']
X = shuffled.drop('label', axis=1)

from sklearn import (
    ensemble, linear_model, neighbors, svm, tree, naive_bayes,
    gaussian_process, neural_network, dummy)
from sklearn.model_selection import KFold
from sklearn.base import clone
from tqdm import tqdm

# fuehre PCA durch
pca = PCA()
# diese matrix ist X * W, das bedeutet, die alte Matrix X * die matrix der Eigenvektoren
transformed = pca.fit_transform(X)

# dies sind die eigenwerte der covariance matrix (siehe documentation)
eigenvalues = pca.explained_variance_
print(eigenvalues)

# for i in range(117):
#     plt.title('Histogramm bezüglich der Dimension {}'.format(i))
#     plt.hist(transformed[:, i], bins=50,
#              range=[transformed[:, i].min(), transformed[:, i].max()],
#              histtype='step', density=True)
#     plt.savefig('../plots/hist_dim_{}.pdf'.format(i))
#     plt.clf()

X_new = transformed[:, 0]

# for i in range(117):
#     X_new2 = transformed[:, i]
#     plt.scatter(X_new, X_new2, c=y, s=50, cmap=discrete_cmap)
#     plt.title("feature 0 und feature {}".format(i))
#     plt.xlabel('feature 0')
#     plt.ylabel('feature {}'.format(i))
#     plt.savefig('../plots/after_pca_{}.pdf'.format(i))
#     plt.clf()
