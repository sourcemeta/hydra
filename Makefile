# Programs
CMAKE = cmake
CTEST = ctest
# For testing
NODE = node

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
		--component sourcemeta_core
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_core_dev
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra_dev

lint: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_tidy

test: .always
	$(CMAKE) -E env \
		UBSAN_OPTIONS=print_stacktrace=1 \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--exclude-regex e2e \
			--output-on-failure --progress --parallel

doxygen: .always
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

clean: .always
	$(CMAKE) -E rm -R -f build

# E2E Testing

HTTP_STUB_PORT = 9999
up-http-stub: test/e2e/http/stub.js .always
	$(NODE) $< $(HTTP_STUB_PORT)

test-e2e: configure compile
	$(CMAKE) -E env \
		UBSAN_OPTIONS=print_stacktrace=1 \
		SOURCEMETA_HYDRA_TEST_HTTP_BASE_URL=http://localhost:$(HTTP_STUB_PORT) \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--tests-regex e2e \
			--output-on-failure --progress --parallel

# For NMake, which doesn't support .PHONY
.always:
