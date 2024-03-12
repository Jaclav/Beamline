#!/bin/bash
ps aux | grep sim | while read a b c;
do
kill -9 $b
done