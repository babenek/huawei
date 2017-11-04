#!/bin/bash




for ext in BIL dat
do
    find . -type f -name *.$ext -print0 | while IFS= read -r -d $'\0' billfile; 
    do
		echo $billfile
		./billsort $billfile >$billfile.sql
		psql -q -U postgres -d billsort -f $billfile.sql
		#| sed "s|(\(.*\));|insert into bill values(\1,'$billfile');|" 
    done
done



#| sed 's/(\(.*\)/insert into bil values(\1/'

#find . -type f -exec ./billsort {} \; | sed 's/(\(.*\)/psql -U postgres -d bilsort -c "insert into bil values(\1";/'
