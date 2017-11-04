#!/bin/bash

DBNAME=dev_babenko

START_TIME=`date +"%Y%m%d_%H%M%S"`

PGPASSWORD=gjcnuhtc
HOST=106.125.46.105

for json in `cat $1`
do
#    echo "select ticket_insert('tickets','$json');"	
	psql -A -t -h $HOST -U postgres --dbname=$DBNAME -c "select ticket_insert('tickets','$json');"
done


################################################################################################


#pg_dump --host jamal.surc.kiev.ua --port 5432 --username "postgres" -w  --format plain --schema-only --encoding SQL_ASCII --verbose --file tmpMrsDataBase.sql "mrs"

STOP_TIME=`date +"%Y%m%d_%H%M%S"`

echo "START: $START_TIME"
echo "STOP: $STOP_TIME"

