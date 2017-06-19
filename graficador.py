import csv
import numpy as np
import matplotlib.pyplot as plt


def Main():
	crecimiento = []
	frontera = []
	weas = []
	with open("reslocal.txt","r") as ifile:
		reader = csv.reader(ifile)
		for row in reader:
			crecimiento.append(row[0])
			frontera.append(row[1])
	ifile.close()
	plt.plot(crecimiento,frontera)
	plt.show()

Main()