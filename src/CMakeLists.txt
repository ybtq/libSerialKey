aux_source_directory(. srcs)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 之前的添加动态库/静态库的方法
# 缺点：动态库与静态库的名字不能重名
# add_library(person SHARED ${srcs})

# 生成动态库目标
add_library(SerialKey SHARED ${srcs})
# 生成静态库目标
add_library(SerialKey_static STATIC ${srcs})

# 指定动态库的输出名称
set_target_properties(SerialKey PROPERTIES OUTPUT_NAME "SerialKey")

# 指定静态库的输出名称
set_target_properties(SerialKey_static PROPERTIES OUTPUT_NAME "SerialKey")

# 使动态库和静态库同时存在
set_target_properties(SerialKey PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(SerialKey_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 指定动态库版本
# VERSION 动态库版本
# SOVERSION API版本
# 这句会导致动态库的名字变成libSerialKey.so.1.0，暂时没这个需要
#set_target_properties(SerialKey PROPERTIES VERSION 1.0 SOVERSION 1)
