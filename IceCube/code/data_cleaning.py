import numpy as np
import matplotlib.pyplot as plt
import pandas

# daten einlesen als csv
sig = pd.read_csv('.csv', delimiter=',')
bkg = pd.read_csv('.csv', delimiter=',')

# daten einlesen als hdf5,
sig = pd.read_hdf('.h5', key='')
sig = pd.read_hdf('.h5', key='')

# features droppen die true daten erhalten
sig.drop([''], axis=1, inplace=True)
bkg.drop([''], axis=1, inplace=True)

remove_NaN = np.nan_to_num(array_welches_nan_enthaellt)
for i in range(len(array_with_inf)):
    if np.isinf(array_with_inf[i]):
        array_with_inf[i] = 0
