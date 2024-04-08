#!/bin/zsh
echo "counts={"
ls . | sort -g | while read b;
do
	#script to get number of perpendicular and parallel counts
	min=$b
	min=${min#*/}
	min=$((min*0*1000))
	echo "#Minimal energy:$min"
	echo "${b#*/}:{"
	i=5
	ls $b/*.csv | while read a;
	do
		echo -n $i":["
		echo -n `grep "neutron;detPerp" $a| awk -F";" '{if($6 > '$min'){print $6}}' | wc -l`
		echo -n ","`grep "neutron;detPara" $a | awk -F";" '{if($6 > '$min'){print $6}}'| wc -l` "]"
		echo ","
		i=$((i+5))
	done
	echo "},"
done
echo "}"