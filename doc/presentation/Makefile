all : slides manual cr


slides :
	pdflatex slides.tex

manual :
	pdflatex manuel/manuel.tex


cr :
	pdflatex -output-directory="compteRendu"  compteRendu/cr.tex

clean :
	rm -rf *.aux *.log *.nav *.out *.snm *.toc *.vrb *.pdf
