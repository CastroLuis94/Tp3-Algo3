constructiva:
	g++ -std=c++11 constructiva.cpp coloreo.cpp -o constructiva
local:
	g++ -std=c++11 local.cpp coloreo.cpp -o local
grasp:
	g++ -std=c++11 nuevograsp.cpp coloreo.cpp -o grasp
adaptativa:
	g++ -std=c++11 adaptativa.cpp coloreo.cpp -o adaptativa
experimentacion:
	g++ -std=c++11 exp_chica.cpp coloreo.cpp -o exp_chica

all:	constructiva local grasp adaptativa experimentacion

clean:
	rm exp_chica adaptativa local constructiva