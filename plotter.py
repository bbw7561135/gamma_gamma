from matplotlib.pyplot import cm
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.lines as lines
import matplotlib.patches as patches

from matplotlib.ticker import MaxNLocator
import matplotlib.gridspec as gridspec

import warnings

import matplotlib
matplotlib.rcParams['text.usetex'] = True
matplotlib.rcParams['text.latex.unicode'] = True

# fig.suptitle('Mean intensity &\ncircular polarization', y=1.05, fontsize=18)

for i in range(5000):
    if (i+1) % 50 != 0:
        continue
    fig, ax = plt.subplots()

    x, y, z = np.loadtxt('dats/time_' + str(i + 1) + '.dat', unpack = True, usecols = (0, 1, 2))
    z += 1;
    z = np.log10(z)
    N = np.sqrt(len(x)) # Only if squared, adjust accordingly
    x = x.reshape((N, N))
    y = y.reshape((N, N))
    z = z.reshape((N, N))
    strm = ax.pcolormesh(x, y, z)
    fig.colorbar(strm)


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
