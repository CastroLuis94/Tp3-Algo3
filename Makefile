constructiva:
	g++ -std=c++11 constructiva.cpp coloreo.cpp -o constructiva
local:
	g++ -std=c++11 local.cpp coloreo.cpp -o local
grasp:
	g++ -std=c++11 grasp.cpp coloreo.cpp -o grasp
adaptativa:
	g++ -std=c++11 adaptativa.cpp coloreo.cpp -o adaptativa
adaptativa_con_random:
	g++ -std=c++11 adaptativa_con_random.cpp coloreo.cpp -o adaptativa_random
experimentacion:
	g++ -std=c++11 exp_chica.cpp coloreo.cpp -o exp_chica
exacto:
		g++ -std=c++11 ejercicio2.cpp coloreo.cpp -o exacto

all:	constructiva local grasp adaptativa experimentacion exacto adaptativa_con_random experimentacion

clean:
	rm exp_chica adaptativa local constructiva exacto adaptativa_random grasp