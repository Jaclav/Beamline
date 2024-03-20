#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
for (( i=5; i<=90; i+=5 ))
do
	echo $i `./sim $i 100 13 | grep ParticleCounts` >> data.txt
done