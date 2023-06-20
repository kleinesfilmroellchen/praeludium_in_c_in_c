TEX			=pdflatex
SOURCE		=document.tex
SOURCE_BARE:=$(patsubst %.tex,%,$(SOURCE))


all: compile

.PHONY: compile
compile: $(SOURCE_BARE).pdf

$(SOURCE_BARE).pdf: $(SOURCE)
	$(TEX) -halt-on-error $<

.PHONY: clean
clean:
	rm -f $(addprefix ${SOURCE_BARE}., aux bbl blg lof log mw out pdf tdo toc)

.PHONY: spellcheck
spellcheck-en:
	aspell --lang=en_US check ${SOURCE}; done
