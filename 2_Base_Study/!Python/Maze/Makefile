.PHONY: all install uninstall clean dvi dist tests

all: run

install:
	@echo "Installing the application..."

uninstall:
	@echo "Uninstalling the application..."

clean:
	@echo "Cleaning up..."
	find . -type f -name '*.pyc' -delete
	find . -type d -name '__pycache__' -delete

dvi:
	@echo "Generating documentation..."

dist:
	@echo "Packaging application for distribution..."

tests:
	@echo "Running tests..."
	pytest tests/

run:
	python3 src/main.py
