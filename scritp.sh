#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
echo 0.1 `./sim 45 100 0.1 | grep ParticleCounts` >> data.txt
echo 0.2 `./sim 45 100 0.2 | grep ParticleCounts` >> data.txt
echo 0.5 `./sim 45 100 0.5 | grep ParticleCounts` >> data.txt
echo 0.7 `./sim 45 100 0.7 | grep ParticleCounts` >> data.txt
for (( i=1; i<=16; i+=1 ))
do
	echo $i `./sim 45 100 $i | grep ParticleCounts` >> data.txt
done