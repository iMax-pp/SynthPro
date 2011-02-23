## Makefile de compilation LaTeX

# Règle générale compilant toutes les cibles LaTeX.
all: slides manual report

# Sous-règles pour facilité la compilation des éléments seuls.
slides: slides/slides.pdf
manual: manuel/manuel.pdf
report: compteRendu/cr.pdf

# Règle de compilation pour les slides.
slides/slides.pdf: slides/slides.tex
	pdflatex -draftmode -output-directory="slides" $^ && pdflatex -output-directory="slides" $^


# Règle de compilation pour le manuel utilisateur.
manuel/manuel.pdf: manuel/manuel.tex
	pdflatex -draftmode -output-directory="manuel" $^ && pdflatex -output-directory="manuel" $^

# Règle de compilation pour le compte-rendu.
compteRendu/cr.pdf: compteRendu/cr.tex compteRendu/ConceptionPIM.tex compteRendu/CompteRendu_Intro.tex compteRendu/ConceptionPIM.tex compteRendu/ConceptionPSM.tex compteRendu/ModeleMetier.tex  compteRendu/PSM_LeMoteurAudio.tex  compteRendu/Tests-et-Validation.tex
	pdflatex -draftmode -output-directory="compteRendu" compteRendu/cr.tex &&  pdflatex  -output-directory="compteRendu" compteRendu/cr.tex

# Régle d'exécution du script de conversion des images SVG -> PDF.
svg2pdf:
	../img/svg2pdf.sh

# Règles de nettoyages des dossiers.
.PHONY: clean nuke

# Nettoie simplement les fichiers générés par LaTeX.
clean:
	rm -rf **/*.aux **/*.log **/*.nav **/*.out **/*.snm **/*.toc **/*.vrb

# Nettoie les fichiers générés par LaTeX, ainsi que le PDF.
nuke: clean
	rm -rf **/*.pdf

