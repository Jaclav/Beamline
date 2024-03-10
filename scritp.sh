#!/bin/bash
for i in {0..100}
do
	echo $i `./sim $i >/dev/null 2> a.txt && grep NN a.txt | wc`
done