# Delegating wrapper. CMake is the build system; this file only shortens the commands typed often, and
# binds each target to the configuration it belongs to, so that `make tests` cannot run without assertions.
#
# Configuring happens on demand: a target configures its own preset the first time it is used.
# `make configure` sets up both at once instead.

JOBS := $(shell nproc)

.PHONY: all dev tests docs install configure

all: build/release/CMakeCache.txt
	cmake --build build/release --parallel $(JOBS) -- --no-print-directory

dev: build/debug/CMakeCache.txt
	cmake --build build/debug --parallel $(JOBS) -- --no-print-directory

tests: build/debug/CMakeCache.txt
	cmake --build build/debug --parallel $(JOBS) --target tests -- --no-print-directory

docs: build/release/CMakeCache.txt
	cmake --build build/release --parallel $(JOBS) --target docs -- --no-print-directory

# Installs what the release build produced, and deliberately does not build it: as a prerequisite of an
# install run under sudo, the build would run as root and leave build/release owned by root.
install:
	cmake --install build/release

configure: build/release/CMakeCache.txt build/debug/CMakeCache.txt

# Configures the preset named by the folder. Editing CMakePresets.json does not trigger this, since the
# cache file still exists; remove the folder to reconfigure from scratch.
build/%/CMakeCache.txt:
	cmake --preset $*
