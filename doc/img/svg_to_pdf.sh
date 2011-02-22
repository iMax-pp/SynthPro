#!/bin/sh

for file in `ls svg/*.svg`
  do
    echo $file
    rsvg -w 2000 $file  ps/`basename $file .svg`.pdf
  done
