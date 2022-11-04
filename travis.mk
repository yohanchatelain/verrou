SHELL = /bin/bash

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(abspath $(dir $(mkfile_path)))

valgrind_path := $(abspath $(current_dir)/../valgrind+verrou)
verrou_path := $(abspath $(valgrind_path)/verrou)
install_path := $(abspath $(verrou_path)/install)

cd_verrou= cd $(verrou_path)
cd_valgrind= cd $(valgrind_path)

source_verrou= source $(install_path)/env.sh
source_interflop= source $(install_path)/interflop-env.sh

debug-variables:
	@echo "*** DEBUG VARIABLES ***"
	@echo "mkfile_path := ${mkfile_path}"
	@echo "current_dir := ${current_dir}"
	@echo "valgrind_path := ${valgrind_path}"
	@echo "verrou_path := ${verrou_path}"
	@echo "install_path := ${install_path}"

download-valgrind:
	cd .. && git clone --branch=$(VALGRIND_VERSION) --single-branch git://sourceware.org/git/valgrind.git $(valgrind_path) >/dev/null

patch-valgrind:
	$(cd_valgrind) && cp -a $(PWD) $(verrou_path)
	$(cd_valgrind) && patch -p1 <$(verrou_path)/valgrind.diff

patch-error:
	$(cd_valgrind) && find . -name '*.rej' | xargs tail -n+1
	# try to build verrou anyway if we check the development version of Valgrind
	test "$(VALGRIND_VERSION)" = "master"

configure:
	@echo "*** INTERFLOP-STDLIB ***"
	./install-interflop.sh $(install_path)

	@echo "*** AUTOGEN ***"
	$(cd_valgrind) && $(source_interflop) && ./autogen.sh

	@echo "*** CONFIGURE ***"
	$(cd_valgrind) && \
	$(source_interflop) && \
	./configure --enable-only64bit --enable-intrinsic-fma --prefix=$(install_path)

build:
	@echo "*** MAKE ***"
	$(cd_valgrind) && make

	@echo "*** MAKE INSTALL ***"
	$(cd_valgrind) && make install

check-install:
	@echo "*** CHECK VERSION ***"
	$(source_verrou) && valgrind --version

	@echo "*** CHECK HELP ***"
	$(source_verrou) && valgrind --tool=verrou --help

check:
	@echo "*** BUILD TESTS ***"
	$(cd_valgrind) && make -C tests  check
	$(cd_valgrind) && make -C verrou check

	@echo "*** VALGRIND TESTS ***"
	$(cd_valgrind) && perl tests/vg_regtest verrou

check-error:
	$(cd_verrou)/tests && tail -n+1 *.stdout.diff *.stdout.out *.stderr.diff *.stderr.out
	@false

unit-test:
	@echo "*** UNIT TESTS ***"
	$(cd_verrou)/unitTest && VFC_BACKENDS_LOGGER=False make
