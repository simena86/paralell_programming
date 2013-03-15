#!/bin/sh
##
main_file=$(ls * | grep '.tex$' | xargs grep "begin{document}" -sl)
main_file=${main_file%".tex"}

#compile two times to get the reference alright
latex -shell-escape -synctex=1 "$main_file.tex"
latex  -shell-escape -synctex=1 "$main_file.tex"
dvips "$main_file.dvi" && ps2pdf "$main_file.ps"

#searching for main_files that dosnt end with .tex and moving them to build
ls * | grep "$main_file" | 
while read line ; do 
	echo $line
	if echo $line | grep -Eq 'tex$|pdf$|gz$|sty$|lst$|pyg$|vrb$' 
	then
		echo "not moving tex file"
	else
		echo "do nothing"		#		mv $line ./build
	fi
done

texworks $main_file.pdf
