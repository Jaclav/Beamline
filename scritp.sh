#!/bin/bash
make
cp data.txt data.txt.bak
echo `date` > data.txt
for (( i=5; i<=110; i+=10 ))
do
	( echo $i `./sim $i 100 10 | grep n0 | wc -l` >> data.txt &)
done