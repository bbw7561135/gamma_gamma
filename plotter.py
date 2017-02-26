from matplotlib.pyplot import cm
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.lines as lines
import matplotlib.patches as patches
import matplotlib.colors as colors

from matplotlib.ticker import MaxNLocator
import matplotlib.gridspec as gridspec

import warnings

import matplotlib
# matplotlib.rcParams['text.usetex'] = True
# matplotlib.rcParams['text.latex.unicode'] = True

minim = 54000
maxim = 84000

for i in range(maxim):
    if (i+1) <= minim:
        continue
    if (i+1) % 1000 != 0:
        continue
    fig, ax = plt.subplots()

    x, y, z = np.loadtxt('dats/time_' + str(i + 1) + '.dat', unpack = True, usecols = (0, 1, 2))
    z += 1;
    z[z==1] = np.nan
    z = np.ma.array (z, mask=np.isnan(z))
    cmap = matplotlib.cm.jet
    cmap.set_bad('black',1.)

    # z = np.log10(z)
    N = np.sqrt(len(x)) # Only if squared, adjust accordingly
    x = x.reshape((N, N))
    y = y.reshape((N, N))
    z = z.reshape((N, N))
    strm = ax.pcolormesh(x, y, z, norm=colors.LogNorm(vmin=z.min(), vmax=z.max()), cmap=cmap)
    cbar = fig.colorbar(strm)
    cbar.set_ticks(np.linspace(z.min(), z.max(), min(10, z.max() - 1)))
    cbar.set_ticklabels(np.floor(np.linspace(z.min() - 1, z.max() - 1, min(10, z.max() - 1))))


    # nX = X.reshape(len(X), len(Z)).T
    # nZ = Z.reshape(len(X), len(Z)).T
    # NN = NN.reshape(len(X), len(Z)).T

    ax.set_aspect(1)

    # with warnings.catch_warnings():
    #     warnings.simplefilter("ignore", UserWarning)
    #     gs.tight_layout(fig)
    print i+1
    plt.savefig('dats/time_' + str(i + 1) + '.png', dpi=100, bbox_inches='tight')
# plt.show()
