#!/bin/bash
for i in {65,70,75,80,85,90,95,100}
do
	echo $i `./sim $i 50 >/dev/null 2> a.txt && grep NN a.txt | wc -l` > data.txt
done