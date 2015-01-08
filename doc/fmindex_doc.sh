#! usr/bin/bash

pdflatex --shell-escape fmindex_doc.tex
bibtex fmindex_doc.aux
pdflatex --shell-escape fmindex_doc.tex
pdflatex --shell-escape fmindex_doc.tex
open fmindex_doc.pdf

#	brisemo sav meta shit
rm *.dv *.bbl *.aux *blg *.dvi *.log *.gz *.toc
