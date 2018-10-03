typeset -i start_cut=0
typeset -i end_cut=1000
typeset -i delta=5

for ((i=$start_cut;i<=$end_cut;i=i+$delta))
do
echo $i >> bins_1.in
done
