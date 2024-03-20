#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
for (( i=2; i<=90; i+=2 ))
do
	echo $i `./sim $i 100 10 | grep ParticleCounts` >> data.txt
done