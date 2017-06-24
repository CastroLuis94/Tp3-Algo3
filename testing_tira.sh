make all;
echo "Genero las entradas ";
python3 generador_tira.py 1000 500 25 > entrada1;
python3 generador_tira.py 1500 750 49 > entrada2;
python3 generador_tira.py 2000 1000 64 > entrada3;
python3 generador_tira.py 2500 1250 100 > entrada4;
python3 generador_tira.py 3000 1500 144 > entrada5;
echo "Corro constructiva";
./constructiva < entrada1 >> resultado_tira/test_constructiva;
./constructiva < entrada2 >> resultado_tira/test_constructiva;
./constructiva < entrada3 >> resultado_tira/test_constructiva;
./constructiva < entrada4 >> resultado_tira/test_constructiva;
./constructiva < entrada5 >> resultado_tira/test_constructiva;

echo "Corro adaptativa random";
./adaptativa_random < entrada1 >> resultado_tira/test_adaptativa_random;
./adaptativa_random < entrada2 >> resultado_tira/test_adaptativa_random;
./adaptativa_random < entrada3 >> resultado_tira/test_adaptativa_random;
./adaptativa_random < entrada4 >> resultado_tira/test_adaptativa_random;
./adaptativa_random < entrada5 >> resultado_tira/test_adaptativa_random;

echo "Corro local";
./local < entrada1 >> resultado_tira/test_local;
./local < entrada2 >> resultado_tira/test_local;
./local < entrada3 >> resultado_tira/test_local;
./local < entrada4 >> resultado_tira/test_local;
./local < entrada5 >> resultado_tira/test_local;

echo "Corro Grasp";
./grasp < entrada1 >> resultado_tira/test_grasp;
./grasp < entrada2 >> resultado_tira/test_grasp;
./grasp < entrada3 >> resultado_tira/test_grasp;
./grasp < entrada4 >> resultado_tira/test_grasp;
./grasp < entrada5 >> resultado_tira/test_grasp;
echo "Borro la entrada"
rm entrada1 entrada2 entrada3 entrada4 entrada5;