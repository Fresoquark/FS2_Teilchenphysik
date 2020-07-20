Prefix = SMD
############################################################

# Automatisch ermittelter Name
Filename = $(addprefix $(Prefix)_, $(addsuffix .pdf,$(notdir $(CURDIR))))
# LaTeX-Optionen, um unnötiges Generve auszuschalten
TeXOptions = --lualatex \
	     --output-directory=build \
	     --interaction=batchmode \
	     --halt-on-error \

ifeq (,$(shell sh -c 'cygpath --version 2> /dev/null'))
  # Unix
  pwd := $$(pwd)
  translate = $1
else
  # Windows mit MSys2/Cygwin
  pwd := $$(cygpath -m "$$(pwd)")
  translate = $(shell echo '$1' | sed 's/:/;/g')
endif

all: build/main.pdf FORCE

# hier weitere Abhängigkeiten für build/main.pdf deklarieren:
build/main.pdf: FORCE | build
	  TEXINPUTS="$(call translate,build:)" \
	  BIBINPUTS=build: \
	  max_print_line=1048576 \
	  latexmk $(TeXOptions) main.tex
	  cp build/main.pdf build/$(Filename)

build:
	mkdir -p build

# plots:
# 	mkdir -p plots

clean:
	rm -rf build
	# rm -rf plots

FORCE:

.PHONY: all clean
