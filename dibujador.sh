
#!/bin/bash

python3 generador_completo.py > grafo1.txt
python3 txtToGraph1.py < grafo1.txt &
g++ -std=c++11 ejercicio2.cpp coloreo.cpp -o ejecutable
./ejecutable < grafo1.txt > salida.txt
python3 txtToGraph2.py
