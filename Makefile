# Programs
CMAKE = cmake
CTEST = ctest
KRAFT = kraft
# For test server
NODE = node
KILLALL = killall
SLEEP = sleep

# Options
PRESET = Debug
SHARED = OFF

all: configure compile test

configure: .always
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON \
		-DHYDRA_TESTS:BOOL=ON \
		-DHYDRA_DOCS:BOOL=ON \
		-DBUILD_SHARED_LIBS:BOOL=$(SHARED)

compile: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_format
	$(CMAKE) --build ./build --config $(PRESET) --parallel 4
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra_dev

lint: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_tidy

test: test/http/stub.js .always
	$(KILLALL) $(NODE) || true
	$(NODE) $< &
	$(SLEEP) 1
	$(CMAKE) -E env UBSAN_OPTIONS=print_stacktrace=1 \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--output-on-failure --parallel
	$(KILLALL) $(NODE)

doxygen: .always
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

# TODO: Fix having to cd to the path
unikraft: .always
	cd unikraft && $(KRAFT) build --target development --jobs 4 --log-type=basic
	cd unikraft && $(KRAFT) run --target development

clean: .always
	$(CMAKE) -E rm -R -f build unikraft/.unikraft unikraft/.config*

# For NMake, which doesn't support .PHONY
.always:
