#!/bin/bash

for file in `find $1 -type f | sort`
do
	#echo $file
	dd if=$file of=$2 oflag=append conv=notrunc
done