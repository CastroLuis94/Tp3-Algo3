
main:  exacto constructiva adaptativa_con_random local_normal local_debuggeo grasp 
constructiva:
	g++ -std=c++11 constructiva.cpp coloreo.cpp -o constructiva
local_normal:
	g++ -std=c++11 local.cpp coloreo.cpp -o local_normal
local_random:
	g++ -std=c++11 local_con_random.cpp coloreo.cpp -o local_random

local_debuggeo:
	g++ -std=c++11 local_debuggeo.cpp coloreo.cpp -o local_debuggeo	
grasp:
	g++ -std=c++11 grasp.cpp coloreo.cpp -o grasp
adaptativa:
	g++ -std=c++11 adaptativa.cpp coloreo.cpp -o adaptativa
adaptativa_con_random:
	g++ -std=c++11 adaptativa_con_random.cpp coloreo.cpp -o adaptativa_random
exacto:
	g++ -std=c++11 ejercicio2.cpp coloreo.cpp -o exacto
exp_chica:
	g++ -std=c++11 exp_chica.cpp coloreo.cpp -o exp_chica;
exp_grande:
	g++ -std=c++11 exp_grande.cpp coloreo.cpp -o exp_grande;

experimentacion:	exp_chica exp_grande
all:	constructiva local local_debuggeo grasp adaptativa experimentacion exacto adaptativa_con_random experimentacion

clean:
	rm exp_chica exp_grande adaptativa local_normal local_debuggeo constructiva exacto adaptativa_random grasp
