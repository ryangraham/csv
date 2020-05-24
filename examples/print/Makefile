all:
	@echo "run - clean, build, and run"
	@echo "clean - remove built files"

run: clean build
	cd build && $(MAKE) run

.PHONY: build
build:
	cd build && cmake .. && $(MAKE)

clean:
	rm -rf ./build/* || true