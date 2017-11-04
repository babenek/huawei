#!/bin/bash

DBNAME=billsort

START_TIME=`date +"%Y%m%d_%H%M%S"`

mkdir -p $START_TIME

#ls -al $BAK_DIR_ROOT

tables=(`psql -A -t -U postgres -c "select table_name from information_schema.tables where table_type='BASE TABLE' and table_schema='public';" --dbname=$DBNAME`)

for table in "${tables[@]}"
do
    echo "$START_TIME backup table: $table"
    pg_dump \
        --username "postgres" \
        --no-password \
        --format=plain \
        --column-insert \
        --inserts \
        --data-only \
        --encoding=SQL_ASCII \
        --verbose \
        --table=$table \
        --dbname=$DBNAME \
        | gzip -9 > $START_TIME.$table.sql.gz
done


################################################################################################


#pg_dump --host jamal.surc.kiev.ua --port 5432 --username "postgres" -w  --format plain --schema-only --encoding SQL_ASCII --verbose --file tmpMrsDataBase.sql "mrs"

STOP_TIME=`date +"%Y%m%d_%H%M%S"`

echo "START: $START_TIME"
echo "STOP: $STOP_TIME"

