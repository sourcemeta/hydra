# Programs
CMAKE = cmake
CTEST = ctest
# For test server
NODE = node
KILLALL = killall
SLEEP = sleep

# Options
PRESET = Debug
SHARED = OFF
TEST_PORT = 9999

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
		--component sourcemeta_jsontoolkit
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsontoolkit_dev
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_hydra_dev

lint: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_tidy

test: test/stub.js .always
	$(KILLALL) $(NODE) || true
	$(NODE) $< $(TEST_PORT) &
	$(SLEEP) 1
	$(CMAKE) -E env \
		UBSAN_OPTIONS=print_stacktrace=1 \
		SOURCEMETA_HYDRA_TEST_SERVER_BASE_URL=http://localhost:$(TEST_PORT) \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--output-on-failure --parallel
	$(KILLALL) $(NODE)

doxygen: .always
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

clean: .always
	$(CMAKE) -E rm -R -f build

# For NMake, which doesn't support .PHONY
.always:
