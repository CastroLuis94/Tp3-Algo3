
#!/bin/bash

python3 generador_completo.py > grafo.txt
python3 txtToGraph1.py < grafo.txt &
g++ -std=c++11 constructiva.cpp coloreo.cpp -o ejecutable
./ejecutable < grafo.txt > salida.txt
python3 txtToGraph2.py
