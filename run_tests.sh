#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

for f in $SCRIPTPATH/tests/*.k
do
	filename="${f##*/}"
	$SCRIPTPATH/build/bin/main $f -o $SCRIPTPATH/build/tests/$filename > q
	diff $SCRIPTPATH/tests/$filename.ll $SCRIPTPATH/build/tests/$filename.ll
done
