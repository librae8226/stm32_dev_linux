# Standard things
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)
BUILDDIRS += $(BUILD_PATH)/$(d)
BUILDDIRS += $(BUILD_PATH)/$(d)/boards
BUILDDIRS += $(BUILD_PATH)/$(d)/tprintf
# BUILDDIRS += ... /* here goes on if more sub dirs */

FRAMEWORK_INCLUDES := -I$(FRAMEWORK_PATH) -I$(FRAMEWORK_PATH)/boards -I$(FRAMEWORK_PATH)/tprintf

# Local flags /* here need more INCLUDES if more sub dirs */
CFLAGS_$(d) := -I$(d) $(LIBMAPLE_INCLUDES) $(FRAMEWORK_INCLUDES) -Wall

# Local rules and targets
cSRCS_$(d) := boards/platform_config.c \
			  system_init.c \
			  ulibc.c \
			  tprintf/tprintf.c \
			  misc.c

cFILES_$(d) := $(cSRCS_$(d):%=$(d)/%)

OBJS_$(d) := $(cFILES_$(d):%.c=$(BUILD_PATH)/%.o)

DEPS_$(d) := $(OBJS_$(d):%.o=%.d)

$(OBJS_$(d)): TGT_CFLAGS := $(CFLAGS_$(d))

TGT_BIN += $(OBJS_$(d))

# Standard things
-include $(DEPS_$(d))
d := $(dirstack_$(sp))
sp := $(basename $(sp))
