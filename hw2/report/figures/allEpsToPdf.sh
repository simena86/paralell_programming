#!/bin/bash



for epsfile in *.eps
do
		#	file=${epsfile%.*eps}
		echo "converting " $epsfile " to " $file".pdf"
		epstopdf  $epsfile
done

