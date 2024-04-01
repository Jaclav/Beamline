#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
for (( i=5; i<=60; i+=10 ))
do
	echo $i `./sim $i 100 30 | grep ParticleCounts` >> data.txt
done