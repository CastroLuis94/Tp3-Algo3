
#!/bin/bash

python3 generador_completo.py > grafo1.txt
python3 txtToGraph1.py < grafo1.txt &
python3 txtToGraph2.py
