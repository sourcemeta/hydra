# Programs
CMAKE = cmake
CTEST = ctest
# For testing
NODE = node
MINIO = minio
MC = mc
MKDIR = mkdir

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
		--component sourcemeta_jsontoolkit
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsontoolkit_dev
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
	$(CMAKE) -E rm -R -f build .data

# E2E Testing

.data:
	$(MKDIR) $@

MINIO_ROOT_USER = sourcemeta
MINIO_ROOT_PASSWORD = sourcemeta
MINIO_PORT = 9000
up-minio: .data .always
	$(CMAKE) -E env \
		MINIO_ROOT_USER=$(MINIO_ROOT_USER) \
		MINIO_ROOT_PASSWORD=$(MINIO_ROOT_PASSWORD) \
		$(MINIO) server --address :$(MINIO_PORT) $</minio

MINIO_ALIAS = sourcemeta
MINIO_ACCESS_KEY = sourcemeta-test
MINIO_SECRET_KEY = 12345678
MINIO_BUCKET = test
MINIO_REGION = us-east-1
MINIO_PROTOCOL = http
MINIO_ADDRESS = 127.0.0.1
configure-minio: .always
	$(MC) alias set $(MINIO_ALIAS) $(MINIO_PROTOCOL)://$(MINIO_ADDRESS):$(MINIO_PORT) \
		$(MINIO_ROOT_USER) $(MINIO_ROOT_PASSWORD)
	$(MC) mb --region $(MINIO_REGION) --ignore-existing $(MINIO_ALIAS)/$(MINIO_BUCKET)
	$(MC) cp --recursive test/e2e/bucket/data $(MINIO_ALIAS)/$(MINIO_BUCKET)
	$(MC) admin user svcacct remove $(MINIO_ALIAS) $(MINIO_ACCESS_KEY) || true
	$(MC) admin user svcacct add \
		--name "Test" \
		--description "Test" \
		--access-key $(MINIO_ACCESS_KEY) \
		--secret-key $(MINIO_SECRET_KEY) \
		$(MINIO_ALIAS) $(MINIO_ROOT_USER)

HTTP_STUB_PORT = 9999
up-http-stub: test/e2e/httpclient/stub.js .always
	$(NODE) $< $(HTTP_STUB_PORT)

test-e2e: configure compile configure-minio
	$(CMAKE) -E env \
		UBSAN_OPTIONS=print_stacktrace=1 \
		SOURCEMETA_HYDRA_TEST_HTTPCLIENT_BASE_URL=http://localhost:$(HTTP_STUB_PORT) \
		SOURCEMETA_HYDRA_TEST_BUCKET_BASE_URL=$(MINIO_PROTOCOL)://$(MINIO_ADDRESS):$(MINIO_PORT)/$(MINIO_BUCKET) \
		SOURCEMETA_HYDRA_TEST_BUCKET_REGION=$(MINIO_REGION) \
		SOURCEMETA_HYDRA_TEST_BUCKET_ACCESS_KEY=$(MINIO_ACCESS_KEY) \
		SOURCEMETA_HYDRA_TEST_BUCKET_SECRET_KEY=$(MINIO_SECRET_KEY) \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--tests-regex e2e \
			--output-on-failure --progress --parallel

# For NMake, which doesn't support .PHONY
.always:
