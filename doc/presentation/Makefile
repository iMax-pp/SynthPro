all : slides manual report


slides: slides/slides.tex
	pdflatex -output-directory="slides" slides/slides.tex

manual:
	pdflatex -output-directory="manuel" manuel/manuel.tex

report:
	pdflatex -output-directory="compteRendu" compteRendu/cr.tex

.PHONY: clean nuke

clean:
	rm -rf **/*.aux **/*.log **/*.nav **/*.out **/*.snm **/*.toc **/*.vrb

nuke: clean
	rm -rf  **/*.pdf
