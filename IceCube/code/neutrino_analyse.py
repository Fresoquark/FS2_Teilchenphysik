import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from project_c1.random import Generator

# nuetzliche angaben
gen = Generator(seed=42)
size = 100000  # anzahl an random values
gamma_r = 1.7 # gamma - 1 aus der integration
size_bg = 10000000  # anzahl an background daten
np.random.seed(13)

# verteilung aus der a.)
def density_function(arr):
    return np.power(1 - arr, -1 / gamma_r)
    # returned ein array

# pick random elements from distribution
def pick_random(arr):
    k = np.random.randint(0, len(arr), len(arr))
    return arr[k]
    # returned eine zahl


# generiere zufallszahlen um die standardnormalverteilung zu erzeugen
x = np.random.default_rng(seed=42).uniform(0, 1, size)
dist_a = density_function(x)

# Warscheinlickeit Energie zu messen
P_E = (1 - np.exp(-dist_a * 0.5))**3

# acceptance array
acc = np.empty(len(P_E), dtype=bool)

# neumann;sche rueckweisung...
gleich_random = np.random.random(size)

# falls random zahl unter unser funktion sitzt -> gut
acc[P_E > gleich_random] = True

# falls random zahl ueber funktion -> False
acc[P_E <= gleich_random] = False

plt.hist(dist_a, bins = 50, histtype = 'step', range = [0.8, 6], lw = 2, label = 'All Energies')
plt.hist(dist_a[acc == True], bins = 50, histtype = 'step', range = [0.8, 6], lw = 2, label = 'acceptance')
plt.yscale('log')
plt.xscale('log')
plt.legend()
plt.grid()
plt.title('Acceptance and raw data')
plt.xlabel('flux')
plt.ylabel('yield')
plt.savefig('plots/project_c1/EnergyAccaptance.pdf')
plt.clf()

# signal values to save in DataFrame
final_x = np.zeros(size)  # koord. x fuer ort
final_y = np.zeros(size)  # koord. y fuer ort
all_hits = np.zeros(size)  # array der hits...
Energy = np.zeros(size)  # ... zu den dazugehoerigen energien

# Background
bg_hits = np.zeros(size_bg)
bg_x = np.zeros(size_bg)
bg_y = np.zeros(size_bg)

E = pick_random(dist_a)  # pick random energy from density distribution
mu_d = 10 * E  # calculate mu
sigma_d = 2 * E  # calculate sigma
distro = gen.normal(mu_d, sigma_d, size)  # generate normal dist with this E
hits = pick_random(distro)  # random zahl aus der energyabhaengigen verteilung "distro"
while len(hits[hits < 0]) > 0:
    hits[hits < 0] = pick_random(distro[hits < 0])
sigma_energy = 1 / np.log10(hits + 1)  # energieabhaengiges sigma fuer orte
x_start = gen.normal(7, sigma_energy, size)  # ziehe random einen x wert aus der verteilung fuer den ort
y_start = gen.normal(3, sigma_energy, size)  # ziehe random einen y wert aus der verteilung fuer den ort

all_hits = hits.astype(int)  # fuelle hits
final_x = pick_random(x_start)  # fuelle koordinate x
final_y = pick_random(y_start)  # fuelle koordinate y
Energy = E  # fuelle energie

# Abfrage: Im Detektor?
while len(final_x[final_x < 0]) > 0 or len(final_x[final_x > 10]) > 0:
    final_x[final_x < 0] = pick_random(x_start[final_x < 0])
    final_x[final_x > 10] = pick_random(x_start[final_x > 10])

while len(final_y[final_y < 0]) > 0 or len(final_y[final_y > 10]) > 0:
    final_y[final_y < 0] = pick_random(y_start[final_y < 0])
    final_y[final_y > 10] = pick_random(y_start[final_y > 10])

# background ermitteln
sigma_bg = 3
mu_bg = 5

# erstelle verteilung aus der die hits gezogen werden, dan ziehe 'random', dann logarithmieren und unten plotten
mu_hits_bg = 2
sigma_hits_bg = 1
# erstelle verteilung aus der die hits gezogen werden sollen
HitDistribution_bg = gen.normal(mu_hits_bg, sigma_hits_bg, size_bg)
# ziehe hits zufaellig aus der obigen verteilung
pull_hits_bg = pick_random(HitDistribution_bg)

# falls hits <= 0 sind neue zufallsverteilung ziehen bis der fall nicht mehr auftritt
while len(pull_hits_bg[pull_hits_bg <= 0]) > 0:
#   new_hits = gen.normal(mu_hits_bg, sigma_hits_bg, len([pull_hits_bg <= 0]))
#   pull_hits_bg[pull_hits_bg <= 0] = new_hits
    pull_hits_bg[pull_hits_bg <= 0] = pick_random(HitDistribution_bg[pull_hits_bg <= 0])

bg_x_start = gen.standard_normal(size_bg)
bg_y_start = gen.standard_normal(size_bg)
# fuelle bg orte
bg_x = pick_random(bg_x_start)
bg_y = pick_random(bg_y_start)

# correlation:
rho = 0.5
def transform_corr(x, y):
    return (np.sqrt(1 - rho**2) * sigma_bg * x) + (rho * sigma_bg * y) + mu_bg


bg_x_new = transform_corr(bg_x, bg_y)
bg_y_new = (sigma_bg * bg_y) + mu_bg

# Abfrage: Im Detektor?
while len(bg_x_new[bg_x_new < 0]) > 0 or len(bg_x_new[bg_x_new > 10]) > 0:
    bg_x_new[bg_x_new < 0] = transform_corr(pick_random(bg_x_start[bg_x_new < 0]),
                                            pick_random(bg_y_start[bg_x_new < 0]))
    bg_x_new[bg_x_new > 10] = transform_corr(pick_random(bg_x_start[bg_x_new > 10]),
                                             pick_random(bg_y_start[bg_x_new > 10]))

while len(bg_y_new[bg_y_new < 0]) > 0 or len(bg_y_new[bg_y_new > 10]) > 0:
    bg_y_new[bg_y_new < 0] = sigma_bg * pick_random(bg_y_start[bg_y_new < 0]) + mu_bg
    bg_y_new[bg_y_new > 10] = sigma_bg * pick_random(bg_y_start[bg_y_new > 10]) + mu_bg

# plotte orte
plt.figure(figsize=(10,10))
plt.hist2d(final_x, final_y, bins=(100,100), cmap = plt.cm.jet)
plt.grid()
plt.title('Orte Signal')
plt.xlim(0,10)
plt.ylim(0,10)
plt.xlabel('x')
plt.ylabel('y')
plt.savefig('plots/project_c1/orte.pdf')
plt.clf()

# for background
plt.figure(figsize=(10,10))
plt.hist2d(bg_x_new, bg_y_new, bins=(100,100), cmap = plt.cm.gist_heat)
plt.grid()
plt.title('Orte Background')
plt.xlim(0,10)
plt.ylim(0,10)
plt.xlabel('x')
plt.ylabel('y')
plt.savefig('plots/project_c1/orte_bg.pdf')
plt.clf()

# hits plotten
plt.hist(HitDistribution_bg, bins=100, range=[-2, 6], histtype='step', density=True, lw=2, label='Normaldist. sigma=1, mu=2')
plt.hist(pull_hits_bg, bins=100, range=[-2, 6], histtype='step', density=True, lw=2,label='hits for background')
plt.grid()
plt.legend()
plt.savefig('plots/project_c1/hits_bg.pdf')
plt.clf()

# speichere werte und baue DataFrame
dict = {'Energy':Energy, 'AcceptanceMask':acc, 'NumberOfHits':all_hits, 'x':final_x, 'y':final_y}
Signal = pd.DataFrame(data=dict)
Signal.to_hdf('NeutrinoMC.h5', key='Signal')

dict_bg = {'NumberOfHits':pull_hits_bg, 'x_bg':bg_x_new, 'y_bg':bg_y_new}
Background = pd.DataFrame(data=dict_bg)
Background.to_hdf('Background.h5', key='Background')

print('Die erzeugten Bilder liegen als PDF in: plots/project_c1/blatt5/')

print(Signal, Background)
