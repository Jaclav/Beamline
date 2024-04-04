#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
for (( i=30; i<=60; i+=5 ))
do
	echo $i `./sim $i 100 10 0 | grep ParticleCounts` >> data.txt
done