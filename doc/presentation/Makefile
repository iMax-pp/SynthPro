## Makefile de compilation LaTeX
# Some useful stuff to compile LaTeX…
LATEX = pdflatex -output-directory=`dirname $^`

# Toujours recompiler compteRendu (peut importe si la cible existe déjà).
.PHONY: compteRendu/*.tex

# Règle générale compilant toutes les cibles LaTeX.
all: slides manuel compteRendu

# Sous-règles pour facilité la compilation des éléments seuls.
slides: svg2pdf slides/slides.pdf
manuel: manuel/manuel.pdf
compteRendu: svg2pdf compteRendu/cr.pdf

# Règle générale de compilation des fichiers tex en PDF.
%.pdf: %.tex
	${LATEX} -draftmode $^
	${LATEX} $^

.PHONY: svg2pdf clean nuke

# Régle d'exécution du script de conversion des images SVG -> PDF.
svg2pdf:
	../img/svg2pdf.sh

# Nettoie simplement les fichiers générés par LaTeX.
clean:
	rm -rf **/*.aux **/*.log **/*.nav **/*.out **/*.snm **/*.toc **/*.vrb

# Nettoie les fichiers générés par LaTeX, ainsi que le PDF.
nuke: clean
	rm -rf **/*.pdf
