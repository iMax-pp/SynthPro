#!/bin/sh

dir=`dirname $0`

mkdir -p $dir/ps

for file in `ls $dir/svg/*.svg`
  do
    echo $file
    rsvg -w 2000 $file $dir/ps/`basename $file .svg`.pdf
  done
