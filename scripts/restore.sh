#!/bin/bash




gzip -cd $1 | psql -q -U postgres -d billsort



