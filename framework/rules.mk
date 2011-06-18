# Standard things
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)
BUILDDIRS += $(BUILD_PATH)/$(d)

FRAMEWORK_INCLUDES := -I$(d)

# Local flags
CFLAGS_$(d) := $(LIBMAPLE_INCLUDES)

# Local rules and targets
cSRCS_$(d) := system_init.c \
			  libc_retarget.c \
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
