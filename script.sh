#!/bin/zsh
make
cp data.txt data.txt.bak
echo `date` > data.txt
for k in {74,26,50,83,82}
do
	mkdir E$k
	for j in {0.5,0.7,1,1.5,2,3,4,5,6,7,8,9,10,11,12,13,14,15}
	do
		mkdir $j
		for (( i=5; i<=30; i+=5 ))
		do
			echo $i $k $j
			# echo $i $j`./sim $i $k $j | grep ParticleCounts` >> data.txt
		done
		mv *.csv $j/
	done
	mv [0-9]* E$k/
done