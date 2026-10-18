# make test   - tool self-tests + every reference solution against its samples
# make lint   - static checks for the Python and shell tooling
# make links  - check every external link in the Markdown (needs network)
# make stress SOL=a.cpp BRUTE=b.cpp GEN=g.py [N=500]

PYTHON ?= python3

.PHONY: test test-tools test-solutions lint links stress

test: test-tools test-solutions

test-tools:
	$(PYTHON) -m unittest discover -s tools/tests -v

test-solutions:
	$(PYTHON) tools/run_tests.py solutions

lint:
	$(PYTHON) -m py_compile tools/*.py tools/tests/*.py templates/stress/*.py templates/interactive/*.py
	bash -n tools/*.sh templates/stress/stress.sh
	@if command -v shellcheck > /dev/null; then shellcheck tools/*.sh templates/stress/stress.sh; fi
	@if command -v ruff > /dev/null; then ruff check tools templates; fi

links:
	tools/check_links.sh

stress:
	templates/stress/stress.sh $(SOL) $(BRUTE) $(GEN) $(or $(N),500)
