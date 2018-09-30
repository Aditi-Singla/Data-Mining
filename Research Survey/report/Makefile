all:
doc=main

all: $(doc).tex
	pdflatex $(doc)
	bibtex $(doc)
	pdflatex $(doc)
	pdflatex $(doc)

clean :
	rm -f $(doc).log
	rm -f $(doc).aux
	rm -f $(doc).dvi
	rm -f $(doc).toc
	rm -f $(doc).lof
	rm -f $(doc).lot
	rm -f $(doc).bbl
	rm -f $(doc).blg
	rm -f $(doc).out
	rm -f $(doc).bcf
	rm -f $(doc).run.xml
