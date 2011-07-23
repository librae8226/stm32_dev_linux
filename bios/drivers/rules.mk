# Standard things
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)
BUILDDIRS += $(BUILD_PATH)/$(d)
BUILDDIRS += $(BUILD_PATH)/$(d)/source
BUILDDIRS += $(BUILD_PATH)/$(d)/source/include
BUILDDIRS += $(BUILD_PATH)/$(d)/source/portable

DRIVER_INCLUDES := -I$(DRIVER_PATH)

# Local flags
CFLAGS_$(d) := -I$(d) $(LIBMAPLE_INCLUDES) -Wall

# Local rules and targets
cSRCS_$(d) := LTM022A69B.c \
              LCD_lib.c

cFILES_$(d) := $(cSRCS_$(d):%=$(d)/%)

OBJS_$(d) := $(cFILES_$(d):%.c=$(BUILD_PATH)/%.o) \
             $(cppFILES_$(d):%.cpp=$(BUILD_PATH)/%.o)
DEPS_$(d) := $(OBJS_$(d):%.o=%.d)

$(OBJS_$(d)): TGT_CFLAGS := $(CFLAGS_$(d))

TGT_BIN += $(OBJS_$(d))

# Standard things
-include $(DEPS_$(d))
d := $(dirstack_$(sp))
sp := $(basename $(sp))
