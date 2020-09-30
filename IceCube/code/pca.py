import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from sklearn.datasets import make_blobs
from sklearn.decomposition import PCA

n_samples = 1000

discrete_cmap = ListedColormap([(0.8, 0.2, 0.3), (0.1, 0.8, 0.3), (0, 0.4, 0.8)])
X, y = make_blobs(n_samples=n_samples, centers=2, n_features=4, random_state=0)

# waehle 2 dimensionen/features
dim1 = X[:, 0]
dim2 = X[:, 1]

dim1_false = X[:, 1]
dim2_false = X[:, 2]
# a.) plots der verteilung
plt.scatter(dim1, dim2, c=y, s=50, cmap=discrete_cmap)
plt.title("vor PCA")
plt.xlabel('feature 0')
plt.ylabel('feature 1')
plt.savefig('../plots/before_pca.pdf')
plt.clf()

plt.scatter(dim1_false, dim2_false, c=y, s=50, cmap=discrete_cmap)
plt.title("vor PCA")
plt.xlabel('feature 0')
plt.ylabel('feature 1')
plt.savefig('../plots/before_pca_false.pdf')
plt.clf()

# fuehre PCA durch
pca = PCA()
# diese matrix ist X * W, das bedeutet, die alte Matrix X * die matrix der Eigenvektoren
transformed = pca.fit_transform(X)

# dies sind die eigenwerte der covariance matrix (siehe documentation)
eigenvalues = pca.explained_variance_
print(eigenvalues)

# hier nehmen wir usn die selben features wie vor der PCA...
X_new1 = transformed[:, 0]
X_new2 = transformed[:, 1]

X_new1_false = transformed[:, 1]
X_new2_false = transformed[:, 2]

# hier plotten wir jedes x' fuer teilaufgabe c.)
for i in range(4):
    plt.title('Histogramm bezüglich der Dimension {}'.format(i))
    plt.hist(transformed[:, i], bins=50,
             range=[transformed[:, i].min(), transformed[:, i].max()],
             histtype='step', density=True)
    plt.savefig('../plots/hist_dim_{}.pdf'.format(i))
    plt.clf()

# ... und pllotten sie
plt.scatter(X_new1, X_new2, c=y, s=50, cmap=discrete_cmap)
plt.title("nach PCA")
plt.xlabel('feature 0')
plt.ylabel('feature 1')
plt.savefig('../plots/after_pca.pdf')
plt.clf()

plt.scatter(X_new1_false, X_new2_false, c=y, s=50, cmap=discrete_cmap)
plt.title("nach PCA")
plt.xlabel('feature 0')
plt.ylabel('feature 1')
plt.savefig('../plots/after_pca_false.pdf')
plt.clf()
