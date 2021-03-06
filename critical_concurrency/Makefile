# use gcc with -fsanitize=thread bc clang on student vms (3.4) has buggy thread
# sanitizer
# this means we also need -ltsan in the link step. libtsan must be installed
# (sudo yum install libtsan on student vms)

OBJS_DIR = .objs

# define all the student executables
EXE_RENDE=rendezvous
EXE_SEM=semamore_tests
EXE_QUEUE=queue_tests
EXE_BAR=barrier_tests
EXES_STUDENT=$(EXE_BAR) $(EXE_SEM) $(EXE_RENDE) $(EXE_QUEUE)

# list object file dependencies for each
OBJS_RENDE=$(EXE_RENDE).o semamore.o
OBJS_SEM=$(EXE_SEM).o semamore.o
OBJS_QUEUE=$(EXE_QUEUE).o queue.o
OBJS_BAR=$(EXE_BAR).o barrier.o

# set up compiler
CC = clang
WARNINGS = -Wall -Wextra -Werror -Wno-error=unused-parameter -Wmissing-declarations -Wmissing-variable-declarations
CFLAGS_DEBUG   = -O0 $(WARNINGS) -g -std=c99 -c -MMD -MP -D_GNU_SOURCE -DDEBUG
CFLAGS_RELEASE = -O2 $(WARNINGS) -g -std=c99 -c -MMD -MP -D_GNU_SOURCE

# tsan needs some funky flags
CFLAGS_TSAN    = $(CFLAGS_DEBUG)
CFLAGS_TSAN    += -fsanitize=thread -DSANITIZE_THREADS -fPIC

# set up linker
LD = clang
LDFLAGS = -lrt -lpthread -fPIC
LDFLAGS_TSAN = $(LDFLAGS) -ltsan

# the string in grep must appear in the hostname, otherwise the Makefile will
# not allow the assignment to compile

IS_VM=$(shell hostname | grep "cs241")
VM_OVERRIDE=$(shell echo $$HOSTNAME)
ifeq ($(IS_VM),)
ifneq ($(VM_OVERRIDE),cs241grader)
$(error This assignment must be compiled on the CS241 VMs)
endif
endif

.PHONY: all
all: release

# build types
# run clean before building debug so that all of the release executables
# disappear
.PHONY: debug
.PHONY: release
.PHONY: tsan

release: $(EXES_STUDENT)
debug:   clean $(EXES_STUDENT:%=%-debug)
tsan:    clean $(EXES_STUDENT:%=%-tsan)

# include dependencies
-include $(OBJS_DIR)/*.d

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# patterns to create objects
# keep the debug and release postfix for object files so that we can always
# separate them correctly
$(OBJS_DIR)/%-debug.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS_DEBUG) $< -o $@

$(OBJS_DIR)/%-release.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS_RELEASE) $< -o $@

$(OBJS_DIR)/%-tsan.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS_TSAN) $< -o $@

# exes
# you will need a triple of exe and exe-debug and exe-tsan for each exe (other
# than provided exes)
$(EXE_BAR): $(OBJS_BAR:%.o=$(OBJS_DIR)/%-release.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_BAR)-debug: $(OBJS_BAR:%.o=$(OBJS_DIR)/%-debug.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_BAR)-tsan: $(OBJS_BAR:%.o=$(OBJS_DIR)/%-tsan.o)
	$(LD) $^ $(LDFLAGS_TSAN) -o $@

$(EXE_RENDE): $(OBJS_RENDE:%.o=$(OBJS_DIR)/%-release.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_RENDE)-debug: $(OBJS_RENDE:%.o=$(OBJS_DIR)/%-debug.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_RENDE)-tsan: $(OBJS_RENDE:%.o=$(OBJS_DIR)/%-tsan.o)
	$(LD) $^ $(LDFLAGS_TSAN) -o $@

$(EXE_QUEUE): $(OBJS_QUEUE:%.o=$(OBJS_DIR)/%-release.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_QUEUE)-debug: $(OBJS_QUEUE:%.o=$(OBJS_DIR)/%-debug.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_QUEUE)-tsan: $(OBJS_QUEUE:%.o=$(OBJS_DIR)/%-tsan.o)
	$(LD) $^ $(LDFLAGS_TSAN) -o $@

$(EXE_SEM): $(OBJS_SEM:%.o=$(OBJS_DIR)/%-release.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_SEM)-debug: $(OBJS_SEM:%.o=$(OBJS_DIR)/%-debug.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_SEM)-tsan: $(OBJS_SEM:%.o=$(OBJS_DIR)/%-tsan.o)
	$(LD) $^ $(LDFLAGS_TSAN) -o $@



.PHONY: clean
clean:
	-rm -rf .objs $(EXES_STUDENT) $(EXES_STUDENT:%=%-debug) $(EXES_STUDENT:%=%-tsan)
