i=5
ls $1/*.csv | while read a;
do
echo -n $i":["
echo -n `grep "proton;detPerp" $a| awk -F";" '{if($6 > 8000){print $6}}' | wc -l`
echo -n ","`grep "proton;detPara" $a | awk -F";" '{if($6 > 8000){print $6}}'| wc -l` "]"
echo ","
i=$((i+5))
done