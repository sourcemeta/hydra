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

# TODO: Make this work on macOS
# TODO: Run using `kraft`
unikraft: test/http/stub.js .always
	mkdir -p build/unikraft/rootfs/etc/ssl/certs
	cp -v /etc/ssl/certs/ca-certificates.crt build/unikraft/rootfs/etc/ssl/certs
	cd unikraft && $(KRAFT) build --target development --jobs 4 --log-type=basic
	$(KILLALL) $(NODE) || true
	$(NODE) $< &
	$(SLEEP) 1
	qemu-system-x86_64 \
		-machine pc,accel=tcg \
		-cpu qemu64,-vmx,-svm,+x2apic,+pdpe1gb \
		-nographic \
		-vga none \
		-rtc base=utc \
		-parallel none \
		-serial stdio \
		-monitor null \
		-netdev user,id=hostnet0 \
		-device virtio-net-pci,netdev=hostnet0,id=net0 \
		-kernel unikraft/.unikraft/build/development_qemu-x86_64 \
		-initrd unikraft/.unikraft/build/initramfs-x86_64.cpio \
		-m 128
	$(KILLALL) $(NODE)

clean: .always
	$(CMAKE) -E rm -R -f build unikraft/.unikraft unikraft/.config*

# For NMake, which doesn't support .PHONY
.always:
