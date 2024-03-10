#!/bin/bash
cp data.txt data.txt.bak
echo `date` > data.txt
for (( i=5; i<=300; i+=10 ))
do
	( echo $i `./sim 45 75 $i >/dev/null 2> a.txt && grep NN a.txt | wc -l` >> data.txt &)
done