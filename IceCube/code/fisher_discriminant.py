import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# daten einlesen
p0 = pd.read_hdf('python/zwei_populationen.h5', key='P_0_10000')
p1 = pd.read_hdf('python/zwei_populationen.h5', key='P_1')

p0_1000 = pd.read_hdf('python/zwei_populationen.h5', key='P_0_1000')
Bins = 100
# fisher als funktion returned den projectionsvector
def fisher_discriminante(signal, backg, name):
    mu_pop1 = np.mean(signal, axis=0)
    mu_pop2 = np.mean(backg, axis=0)
    print("-----mu_1----- {}".format(name))
    print(mu_pop1)
    print("-----mu_2----- {}".format(name))
    print(mu_pop2)

    mittel_1 = np.array([x1 - mu_pop1[0], y1 - mu_pop1[1]])
    mittel_2 = np.array([x2 - mu_pop2[0], y2 - mu_pop2[1]])

    S1 = (mittel_1).dot(np.transpose(mittel_1))
    S2 = (mittel_2).dot(np.transpose(mittel_2))
    Sw = S1 + S2
    print("-----S_1----- {}".format(name))
    print(S1)
    print("-----S_2----- {}".format(name))
    print(S2)
    print("-----S_w----- {}".format(name))
    print(Sw)

    mu_diff = (mu_pop1 - mu_pop2).reshape(1, -1)
    mu_diff_T = mu_diff.reshape(-1, 1) # macht aus zeilen einen spalten vector da 1D arrays nicht transpose verstehen
    SB = mu_diff_T.dot(mu_diff)
    print("-----S_B----- {}".format(name))
    print(SB)

    Sw_inverse = np.linalg.inv(Sw)

    lambda_star = Sw_inverse.dot(mu_diff_T)
    print("-----Lambda----- {}".format(name))
    print(lambda_star)
    print("########################################")

    return lambda_star, mu_pop1, mu_pop2


def projection_x_alt(arr, lambd):
    x = arr[:, 0]
    y = arr[:, 1]
    return (lambd[0]*x+lambd[1]*y)/(lambd[0]**2+lambd[1]**2)*lambd[0]


def efficiency(n_a, n_b, bins_a, bins_b, lamb):
    eff = np.zeros(200)
    N = 0
    for i in lamb:
        tp = np.sum(n_a[bins_a < i])
        fn = np.sum(n_a[bins_a > i])

        eff[N] = tp / (tp + fn)
        N += 1
    return eff


def purity(n_a, n_b, bins_a, bins_b, lamb):
    pur = np.zeros(200)
    N = 0
    for i in lamb:
        tp = np.sum(n_a[bins_a < i])
        fp = np.sum(n_b[bins_b < i])

        pur[N] = tp / (tp + fp)
        N += 1
    return pur


def ssB(n_a, n_b, bins_a, bins_b, lamb):
    ssb = np.zeros(200)
    N = 0
    for i in lamb:
        ssb[N] = np.sum(n_a[bins_a < i]) / (np.sqrt(np.sum(n_a[bins_a < i]) + np.sum(n_b[bins_b < i])))
        N += 1
    return ssb


def sb(n_a, n_b, bins_a, bins_b, lamb):
    N = 0
    SB = np.zeros(100)
    for i in lamb:
        SB[N] = np.sum(n_a[bins_a < i]) / np.sum(n_b[bins_b < i])
        N += 1
    return SB


# ------- ende funktions definittionen ---------

# hier kmmt nun der spass
x1 = p0['x']
y1 = p0['y']

x2 = p1['x']
y2 = p1['y']

x3 = p0_1000['x']
y3 = p0_1000['y']

# signale und backgrounds sinnvoll speichern
sig1 = np.array([x1, y1]).T
sig2 = np.array([x3, y3]).T
bg = np.array([x2, y2]).T

# projectionen aus der fisher methode extrahieren
lambda_star, mu_1, mu_2 = fisher_discriminante(sig1, bg, 'P1_10K')
lambda_star_1000, mu_1_1000, mu_2_1000 = fisher_discriminante(sig2, bg, 'P1_1K')

# berechne projectionen
x1_proj = projection_x_alt(sig1, lambda_star)
x1_1000_proj = projection_x_alt(sig2, lambda_star_1000)
x2_proj = projection_x_alt(bg, lambda_star)

# plotten der verteilungen
plt.scatter(x1, y1, marker=".", label='pop. 1')
plt.scatter(x2, y2, marker=".", label='pop. 2')
plt.plot(mu_1[0], mu_1[1], 'kd', label=r'$\mu_1$')
plt.plot(mu_2[0], mu_2[1], 'kd', label=r'$\mu_2$')
plt.legend()
plt.title('populations')
plt.xlabel('x')
plt.ylabel('y')
plt.grid()
plt.savefig('plots/population.pdf')
plt.clf()

# plot fuer die d.)
(n1, bins1, patches1) = plt.hist(x1_proj, bins=Bins, histtype='step', density=False, lw=2, label='p0 (Signal)')
(n2, bins2, patches2) = plt.hist(x2_proj, bins=Bins, histtype='step', density=False, lw=2, label='p1 (Background)')
(n3, bins3, patches3) = plt.hist(x1_1000_proj, bins=Bins, histtype='step', density=False, lw=2, label='p0_1000')
plt.legend()
plt.title('projected populations')
plt.xlabel('x')
plt.ylabel('No. of x')
plt.grid()
plt.savefig('plots/projection.pdf')
plt.clf()
# bingrenzen
bins1 = 0.5 * (bins1[:-1] + bins1[1:])
bins2 = 0.5 * (bins2[:-1] + bins2[1:])
bins3 = 0.5 * (bins3[:-1] + bins3[1:])
# linspaces zum plotten
lamb1 = np.linspace(bins1[np.argwhere(n1[:len(n1)//2] == 0).max() + 1],
                    bins2[(np.argwhere(n2[len(n2)//2:] == 0)+len(n2)//2).min() - 1], 200)
lamb1_urspr = np.linspace(-3, 2, 200)

lamb1_alt = np.linspace(bins3[np.argwhere(n3[:len(n3)//2] == 0).max() + 1],
                        bins2[(np.argwhere(n2[len(n2)//2:] == 0)+len(n2)//2).min() - 1], 200)
lamb1_alt_urspr = np.linspace(-2.8, 2, 200)

lamb2 = np.linspace(bins2[np.argwhere(n2[:len(n2)//2] == 0).max() + 1],
                    bins2[(np.argwhere(n1[len(n1)//2:] == 0)+len(n1)//2).min() - 1], 100)
lamb2_urspr = np.linspace(-1, 0.5, 100)

# eff, pur,, sb ud ssb berechnen
eff = efficiency(n1, n2, bins1, bins2, lamb1)
Purity = purity(n1, n2, bins1, bins2, lamb1)
SSB = ssB(n1, n2, bins1, bins2, lamb1)
SB = sb(n1, n2, bins1, bins2, lamb2)

eff_other = efficiency(n3, n2, bins3, bins2, lamb1_alt)
Purity_other = purity(n3, n2, bins3, bins2, lamb1_alt)
SSB_other = ssB(n3, n2, bins3, bins2, lamb1_alt)
SB_other = sb(n3, n2, bins3, bins2, lamb2)

# pllotten eff und purity
plt.plot(lamb1, eff, 'r.', label='efficiency')
plt.plot(lamb1, eff_other, 'r--', label='efficiency p0_1000')
plt.plot(lamb1_alt, Purity, 'b.', label='purity')
plt.plot(lamb1_alt, Purity_other, 'b--', label='purity p0_1000')
plt.legend()
plt.grid()
plt.title('eff. and purity')
plt.xlabel(r'$\lambda_{\mathrm{cut}}$')
plt.ylabel('a.U.')
plt.savefig('plots/Eff_Purity.pdf')
plt.clf()

plt.plot(lamb2, SB, 'r.', label=r'$\frac{\mathrm{Signal}}{\mathrm{Background}}$')
plt.plot(lamb2, SB_other, 'b.', label=r'$\frac{\mathrm{other Signal}}{\mathrm{Background}}$')
plt.legend()
plt.grid()
plt.title('Signal / Background')
plt.xlabel(r'$\lambda_{\mathrm{cut}}$')
plt.ylabel('a.U.')
plt.savefig('plots/SB.pdf')
plt.clf()

plt.plot(lamb1, SSB, 'b.', label=r'$\frac{S}{\sqrt{S + B}}$')
plt.plot(lamb1_alt, SSB_other, 'g.', label=r'$\frac{S}{\sqrt{S + B}}$')
plt.vlines(lamb1[np.argmax(SSB)], 0, 100, colors='b', label='maximum significance = {}'.format(format(lamb1[np.argmax(SSB)], '1.4f')))
plt.vlines(lamb1_alt[np.argmax(SSB_other)], 0, 100, colors='g', label='maximum significance = {}'.format(format(lamb1_alt[np.argmax(SSB_other)], '1.4f')))
plt.legend()
plt.ylim(0,100)
plt.grid()
plt.title(r'$\frac{S}{\sqrt{S + B}}$')
plt.xlabel(r'$\lambda_{\mathrm{cut}}$')
plt.ylabel('a.U.')
plt.savefig('plots/SSB.pdf')
plt.clf()
