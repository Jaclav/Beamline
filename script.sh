#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
for (( j=1; j<=15; j+=1 ))
do
	for (( i=5; i<=30; i+=5 ))
	do
		echo $i $j`./sim $i 100 $j 0 | grep ParticleCounts` >> data.txt
	done
done