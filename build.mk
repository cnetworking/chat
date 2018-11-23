TARGET_EXEC ?= $(EXEC).out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src


ifeq ($(EXEC),server)
    NOT := client
endif
ifeq ($(EXEC),client)
    NOT := server
endif


SRCS := $(shell find $(SRC_DIRS) -name *.c -not -name $(NOT).c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o)

CPPFLAGS ?= $(INC_FLAGS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p