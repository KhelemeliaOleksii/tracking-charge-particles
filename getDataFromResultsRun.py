# JSON  https://codereview.stackexchange.com/questions/180266/simple-json-parser-in-c
#       https://www.json.org/json-en.html

# get from: https://stackoverflow.com/questions/42704087/import-dat-file-in-python-3
import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt('resultsRun.dat',
                     #  skip_header=1,
                     #  skip_footer=1,
                     names=True,
                     dtype=None,
                     delimiter='\t')

xInitIndex = data.dtype.names.index("XInit")
yInitIndex = data.dtype.names.index("YInit")
zInitIndex = data.dtype.names.index("ZInit")
rIninitIndexes = [xInitIndex, yInitIndex, zInitIndex]

# print(xInitIndex)
coordsInitial = []
for item in data:
    coordsInitial.append(
        [item[xInitIndex], item[yInitIndex], item[zInitIndex]])

print("Number of particles is", len(coordsInitial))

# get from: https://matplotlib.org/stable/gallery/subplots_axes_and_figures/geo_demo.html

###############################################################################
plt.figure()
plt.subplot(projection="aitoff")
plt.title("Aitoff")
plt.grid(True)
plt.plot(coordsInitial, 'o', markersize=0.5, color="black")
plt.show()
