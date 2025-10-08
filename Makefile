# Programs
CMAKE = cmake
CTEST = ctest
DOCKER = docker

# Options
PRESET = Debug
SHARED = OFF
PREFIX = ./build/dist

all: configure compile test

configure: .always
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON \
		-DSOURCEMETA_HYDRA_TESTS:BOOL=ON \
		-DBUILD_SHARED_LIBS:BOOL=$(SHARED)

compile: .always
	$(CMAKE) --build ./build --config $(PRESET) --parallel 4
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra_dev

test: .always
	$(CTEST) --test-dir ./build --build-config $(PRESET) --output-on-failure --parallel

docker: .always
	$(DOCKER) build . --file Dockerfile --progress plain

clean: .always
	$(CMAKE) -E rm -R -f build
	$(DOCKER) system prune --force --all --volumes || true

# For NMake, which doesn't support .PHONY
.always:
