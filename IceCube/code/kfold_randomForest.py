import numpy as np
from sklearn import (
    ensemble, linear_model, neighbors, svm, tree, naive_bayes,
    gaussian_process, neural_network, dummy)
from sklearn.model_selection import KFold
from sklearn.base import clone
from tqdm import tqdm


def define_model(seed):
    """A helper function to retrieve a model for the energy regression
    exercise. The parameter seed gets used to set the random state of the model
    and ensure reproducible results"""

    model = ensemble.RandomForestRegressor(n_estimators=100)
    # model = dummy.DummyRegressor()

    return model


def cross_validate_model(X, y, model, seed):
    """This function implements a cross validation on a given model.

    Required return values:
    -----------------------
    predictions: np.array of the same shape as y
        (These are the predictions on the test sets combined into one array)
    true_values: np.array of the same shape as y
        (These are the y's chosen in the different cross validation steps
        combined into one array. This equals y but with different order.)
    models: list of (n_cross_validation_steps) models
        These are used to calculate the feature importances later
    """


    cv = KFold(5, shuffle=True, random_state=seed)
    models = []
    predictions = []
    true_values = []
    for train_idx, test_idx in cv.split(X):
        X_train, X_test = X.iloc[train_idx, :], X.iloc[test_idx, :]
        y_train, y_test = y[train_idx], y[test_idx]

        model.fit(X_train, y_train)
        prediction = model.predict(X_test)
        true_value = y_test

        return prediction, true_value, model
    # return np.array(predictions), np.array(true_values), models
