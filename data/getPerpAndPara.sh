#!/bin/zsh
#script to get number of perpendicular and parallel counts
min=$1
min=${min#*/}
min=$((min*.87*1000))
echo "#Minimal energy:$min"
echo "${1#*/}:{"
i=5
ls $1/*.csv | while read a;
do
	echo -n $i":["
	echo -n `grep "proton;detPerp" $a| awk -F";" '{if($6 > '$min'){print $6}}' | wc -l`
	echo -n ","`grep "proton;detPara" $a | awk -F";" '{if($6 > '$min'){print $6}}'| wc -l` "]"
	echo ","
	i=$((i+5))
done
echo "},"