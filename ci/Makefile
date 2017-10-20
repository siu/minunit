CFLAGS += -Wall -Wextra
INCLUDE_DIRS += -I../

LIBS += -lm

# Os-specific settings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lrt
endif

minunit_example: ../minunit_example.c ../minunit.h
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(LIBS) $< -o $@

