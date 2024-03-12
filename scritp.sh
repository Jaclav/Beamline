#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
for (( i=5; i<=100; i+=5 ))
do
	( echo $i `./sim $i 100 15 | grep NN | wc -l` >> data.txt &)
done