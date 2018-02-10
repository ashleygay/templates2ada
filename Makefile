# Makefile
HOST_GCC=g++
TARGET_GCC=gcc
PLUGIN_SOURCE_FILES= plugin.cpp
GCCPLUGINS_DIR:= $(shell $(TARGET_GCC) -print-file-name=plugin)
CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include -fPIC -fno-rtti -O0 -Wall -Wextra

cpp_templates_fix.so: $(PLUGIN_SOURCE_FILES)
	$(HOST_GCC) -shared $(CXXFLAGS) $^ -o $@
test:
	$(HOST_GCC) $(CXXFLAGS) -c -fplugin=./cpp_templates_fix.so test.cpp

.phony: test
