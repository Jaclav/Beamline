#!/bin/zsh
echo "counts={"
ls . | sort -g | while read b;
do
	#script to get number of perpendicular and parallel counts
	min=$b
	min=${min#*/}
	if [ $1 = "neutron" ]
	then
		min=0
	else
		min=$((min*0.9*1000))
	fi

	echo "#Minimal energy:$min"
	echo "${b#*/}:{"
	i=5
	ls $b/*.csv | while read a;
	do
		echo -n $i":["
		echo -n `grep "$1;detPerp" $a| awk -F";" '{if($6 > '$min'){print $6}}' | wc -l`
		echo -n ","`grep "$1;detPara" $a | awk -F";" '{if($6 > '$min'){print $6}}'| wc -l` "]"
		echo ","
		i=$((i+5))
	done
	echo "},"
done
echo "}"