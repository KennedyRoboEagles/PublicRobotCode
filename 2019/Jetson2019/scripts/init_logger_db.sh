#! /bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    exit
fi

database_file=$1
echo "Initializing Logger Database: ${database_file}"
sqlite3 "${database_file}" < "${SRC_TOP}/Logger/sql/init_db.sql"