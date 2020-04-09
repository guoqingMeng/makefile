CXX=g++

CPPFLAGS := -std=c++11 
CPPFLAGS += -Werror=return-type -O3  -pthread
CPPFLAGS += -I./include
CPPFLAGS += -I/usr/local/include
CPPFLAGS += -L/usr/local/lib
LDFLAGS += -Wl,-rpath ./lib
LIB := -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_video

BUILD_PATH := build
LIB_NAME ?= test
STATIC_NAME ?= lib$(LIB_NAME).a
SHARE_NAME  ?= lib$(LIB_NAME).so
EXECUTE_NAME ?= $(LIB_NAME).bin

SRC_MAIN_CPP := $(shell find demo -name "*.cpp")
SOURCE := $(shell find src -name "*.cpp")

TARGET_PATH := lib
STATIC_TARGET := $(TARGET_PATH)/$(STATIC_NAME)
SHARE_TARGET := $(TARGET_PATH)/$(SHARE_NAME)
TARGET_SO_EXE := $(BUILD_PATH)/$(EXECUTE_NAME)
TARGET_NULTI_EXE := $(SRC_MAIN_CPP:%.cpp=$(BUILD_PATH)/%.bin)

OBJS:=$(patsubst %.cpp, $(BUILD_PATH)/%.o, $(SRC_MAIN_CPP))
SOBJS:=$(patsubst %.cpp, $(BUILD_PATH)/%.o, $(SOURCE))  
OBJS+=$(patsubst %.cpp, $(BUILD_PATH)/%.o, $(SOURCE)) 

BUILD_DIR := $(sort $(BUILD_PATH) $(dir $(OBJS)))

DEPS  :=$(OBJS:%.o=%.d) #静态模式（变量值替换，OBJS中所有以o结尾的换成以d结尾的）

all:$(BUILD_DIR) $(TARGET_PATH) $(OBJS) $(STATIC_TARGET)  $(SHARE_TARGET) $(TARGET_SO_EXE) $(TARGET_NULTI_EXE)
#   
.PHONY:all clean
#生成可执行文件
# #静态模式
# #目标集合：目标模式：依赖模式
$(TARGET_NULTI_EXE):%.bin:%.o $(SOBJS) | $(BUILD_DIR) 
	@echo $(CXX) $< $(SOBJS) $@
	$(CXX) -g $(CPPFLAGS) -o $@ $< $(SOBJS) $(LIB)

#依赖生成的so生成可执行文件
$(TARGET_SO_EXE): $(SRC_MAIN_CPP) | $(TARGET_PATH) $(BUILD_DIR) 
	@echo $(CXX) $< $@
	$(CXX) -g $(CPPFLAGS) -L./$(TARGET_PATH) -o $@ $< -ltest  $(LIB) $(LDFLAGS)

#生成静态库
#动态库的调用仍是动态调用，而不是把动态库的相关函数copy到自己身上
$(STATIC_TARGET):$(OBJS)  | $(TARGET_PATH) $(BUILD_DIR) 
	ar rcs $@ $<
	ranlib $@ 

#生成动态库 (.so添加链接库，生成库的依赖关系，若不加就没有依赖关系 ldd ./lib/libtest.so)
$(SHARE_TARGET):$(OBJS) | $(TARGET_PATH) $(BUILD_DIR) 
	@echo $(CXX) $< $@
	$(CXX) -shared -fPIC $(CPPFLAGS) -o $@ $< $(LIB) 

#生成二进制文件
$(OBJS): $(SOURCE) $(SRC_MAIN_CPP) | $(TARGET_PATH) $(BUILD_DIR) 
	@echo $(CXX) $< $@
	$(CXX) $(CPPFLAGS) -fPIC -MMD -MP -c $< -o $@

$(BUILD_DIR):
	@echo mkdir $@
	mkdir -p $(BUILD_DIR)
$(TARGET_PATH):
	@echo mkdir $@
	mkdir -p $(TARGET_PATH)

clean:
	rm -rf $(TARGET_PATH) $(BUILD_DIR)

-include $(DEPS)