# Makefile del repositorio de algoritmos de EDA.
#
#   make          compila TODOS los .cc del repositorio en bin/
#   make clean    borra bin/
#   make list     lista los ejecutables que se generarian
#
# Cada .cc es un programa independiente con su propio main.
# El nombre del ejecutable es <carpeta>-<fichero>, p.ej. bin/Mergesort-merge_sort_1

CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wno-sign-compare -Wno-shadow

SRCS := $(shell find . -name '*.cc' -not -path './bin/*' | sort)
BINS := $(foreach s,$(SRCS),bin/$(shell basename $(dir $(s)))-$(notdir $(basename $(s))))

.PHONY: all clean list

all: $(BINS)
	@echo ""
	@echo "OK: $(words $(BINS)) programas compilados en bin/"

bin:
	@mkdir -p bin

define RULE
bin/$(shell basename $(dir $(1)))-$(notdir $(basename $(1))): $(1) | bin
	@$$(CXX) $$(CXXFLAGS) $$< -o $$@ && echo "  [ok] $$@"
endef

$(foreach s,$(SRCS),$(eval $(call RULE,$(s))))

list:
	@for b in $(BINS); do echo $$b; done

clean:
	@rm -rf bin
	@echo "bin/ borrado"
