#This makefile has to be in the root dir of the proyect
#User configuration
PROYECT_NAME := histograma
DEBUG := #-g
BUILD_DIR := dist
LIBS_DIR := libs
TMP_DIR := /tmp
BENCH_DIR := benchmark
OBJ_DIR := build/.obj
DEP_DIR := build/.deps
EXTRA_LIBS = -lhistograma -lm
WORK_DIR := $(shell pwd)
EXTRA_HEADERS =
HEADERS_DIRS := $(WORK_DIR)
CFLAGS=-g -Wall
SRC_FILES := $(WORK_DIR)/Graficador.c $(WORK_DIR)/main.c
#Include all directories where header files are found
INCLUDES  := $(addprefix -I,$(foreach hdir,$(HEADERS_DIRS),$(shell find $(hdir) -type f -name "*.h" -printf '%h\n' | sort -u)))
OBJ_FILES := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
LDLIBS := $(LIBS_DIR)/libhistograma.so
DEPFILES := $(SRC_FILES:%.c=$(DEP_DIR)/%.d)
DEPFLAGS = -MT $@ -MD -MP -MF $(DEP_DIR)/$<.Td
POSTCOMPILE = mv -f $(DEP_DIR)/$<.Td $(DEP_DIR)/$<.d && touch $@
COMPILE.c = $(CC) -L $(LIBS_DIR) $(DEPFLAGS) $(CFLAGS) $(TARGET_ARCH) -c

.PHONY: all

all: $(OBJ_FILES) $(LDLIBS) | $(BUILD_DIR)
	$(CC) -L $(LIBS_DIR) $(DEBUG) -o $(BUILD_DIR)/$(PROYECT_NAME) $(OBJ_FILES) $(EXTRA_LIBS)

define make-goal
$1 : $2 | $(DEP_DIR)
	$$(COMPILE.c) $$(DEBUG) $$(EXTRA_HEADERS) $$(INCLUDES) -o $$@ $$<
	$$(POSTCOMPILE)
endef

$(LIBS_DIR): ; @mkdir -p $@
$(DEP_DIR): ; @mkdir -p $@
$(BUILD_DIR): ; @mkdir -p $@
$(BENCH_DIR): ; @mkdir -p $@

$(DEPFILES):
include $(wildcard $(DEPFILES))

#Make needed dirs
DIRS_TO_MAKE := $(shell echo $(foreach sfdir,$(SRC_FILES),$(shell dirname $(sfdir))) | xargs -n1 | sort -u | xargs)
$(foreach dir,$(DIRS_TO_MAKE),$(shell mkdir -p $(OBJ_DIR)/$(dir)))
$(foreach dir,$(DIRS_TO_MAKE),$(shell mkdir -p $(DEP_DIR)/$(dir)))
#Create the targets automatically
$(foreach sfile,$(SRC_FILES),$(eval $(call make-goal,$(sfile:%.c=$(OBJ_DIR)/%.o),$(sfile))))

clean:
	@rm -r $(DEP_DIR)
	@rm -r $(BUILD_DIR)
	@rm -r $(OBJ_DIR)
	@rm -r $(BENCH_DIR)

histograma-1: $(LIBS_DIR) $(WORK_DIR)/histograma-1-enum-switch.c
	$(CC) -c -fPIC $(WORK_DIR)/histograma-1-enum-switch.c -o build/histograma-1-enum-switch.o
	$(CC) -shared -o $(LDLIBS) build/histograma-1-enum-switch.o

histograma-2: $(LIBS_DIR) $(WORK_DIR)/histograma-2-goto.c
	$(CC) -c -fPIC $(WORK_DIR)/histograma-2-goto.c -o build/histograma-2-goto.o
	$(CC) -shared -o $(LDLIBS) build/histograma-2-goto.o

histograma-3: $(LIBS_DIR) $(WORK_DIR)/histograma-3-rec.c
	$(CC) -c -fPIC $(WORK_DIR)/histograma-3-rec.c -o build/histograma-3-rec.o
	$(CC) -shared -o $(LDLIBS) build/histograma-3-rec.o

histograma-x: $(LIBS_DIR) $(WORK_DIR)/histograma-x.c
	$(CC) -c -fPIC $(WORK_DIR)/histograma-x.c -o build/histograma-x.o
	$(CC) -shared -o $(LDLIBS) build/histograma-x.o

build-test: $(BUILD_DIR) $(WORK_DIR)/test.c
	$(CC) -L $(LIBS_DIR)  -o $(BUILD_DIR)/test test.c -lhistograma

run-benchmark: build-test $(BENCH_DIR)
	@echo "Extrayendo input de ~5kb"
	@tar -xzvf input/5k.tar.gz -C /tmp
	@echo "Extrayendo input de ~5mb"
	@tar -xzvf input/5m.tar.gz -C /tmp
	@echo "Extrayendo input de ~1gb"
	@tar -xzvf input/1g.tar.gz -C /tmp

	@echo "Ejecucion con input 5136 bytes\n--------------------------------------------" > $(BENCH_DIR)/5kb.txt
	@echo "Ejecucion con input 5248950 bytes\n--------------------------------------------" > $(BENCH_DIR)/5mb.txt
	@echo "Ejecucion con input 1099784999 bytes\n--------------------------------------------" > $(BENCH_DIR)/1gb.txt

	@make histograma-1
	@echo "Histograma 1"

	@-cat $(TMP_DIR)/5k.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5kb.txt
	@-cat $(TMP_DIR)/5m.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5mb.txt
	@-cat $(TMP_DIR)/1g.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/1gb.txt

	@make histograma-2
	@echo "Histograma 2"

	@-cat $(TMP_DIR)/5k.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5kb.txt
	@-cat $(TMP_DIR)/5m.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5mb.txt
	@-cat $(TMP_DIR)/1g.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/1gb.txt

	@make histograma-3
	@echo "Histograma 3"

	@-cat $(TMP_DIR)/5k.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5kb.txt
	@-cat $(TMP_DIR)/5m.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5mb.txt
	@-cat $(TMP_DIR)/1g.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/1gb.txt

	@make histograma-x
	@echo "Histograma x"

	@-cat $(TMP_DIR)/5k.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5kb.txt
	@-cat $(TMP_DIR)/5m.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/5mb.txt
	@-cat $(TMP_DIR)/1g.txt | LD_LIBRARY_PATH=./libs ./$(BUILD_DIR)/test >> $(BENCH_DIR)/1gb.txt

