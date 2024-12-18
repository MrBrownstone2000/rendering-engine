target = Debug

ifneq ($(target), Debug)
	ifneq ($(target), Release)
	  $(error Wrong target)
	endif
endif

.PHONY: clean build runExample

# To print the compilation commands:   -DBUILD_TESTS=ON -DCMAKE_VERBOSE_MAKEFILE=ON
build:
	@cmake -DCMAKE_BUILD_TYPE=$(target) -DBUILD_TESTS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build >> /dev/null
	@cmake --build build --target install -j12

clean:
	@rm -rf install build

runTest: build
	@build/test/EngineTest

runSandbox: build
	@build/sandbox/Sandbox

renderdoc: build
	@qrenderdoc renderdoc-settings.cap
