#!/bin/bash

i=0

while [ $i -lt 5 ]
do
    ./KNN $1 <<< $2
    let i=i+1
done
