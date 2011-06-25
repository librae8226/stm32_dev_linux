# Standard things
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)
BUILDDIRS += $(BUILD_PATH)/$(d)
BUILDDIRS += $(BUILD_PATH)/$(d)/source
BUILDDIRS += $(BUILD_PATH)/$(d)/source/include
BUILDDIRS += $(BUILD_PATH)/$(d)/source/portable

OS_INCLUDES := -I$(OS_PATH) -I$(OS_PATH)/source -I$(OS_PATH)/source/include -I$(OS_PATH)/source/portable

# Local flags
CFLAGS_$(d) := -I$(d) $(LIBMAPLE_INCLUDES) $(OS_INCLUDES) -Wall

# Local rules and targets
cSRCS_$(d) :=  source/croutine.c \
               source/heap_2.c \
               source/list.c \
               source/portable/port.c \
               source/queue.c \
               source/timers.c \
               source/tasks.c \
			   MapleFreeRTOS.c

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
