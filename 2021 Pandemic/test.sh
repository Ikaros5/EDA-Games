for i in {1..50}; do
    echo $i
    ./Game -s $i  Zeus Poseidon Prueba1 MiquelG_v2 < default.cnf >& out.cnf; grep "got score" out.cnf > game.txt
    ./SecGame -s $i   Zeus Poseidon Prueba1 MiquelG_v2 < default.cnf >& out.cnf; grep "got score" out.cnf > sec-game.txt
    diff game.txt sec-game.txt
done
