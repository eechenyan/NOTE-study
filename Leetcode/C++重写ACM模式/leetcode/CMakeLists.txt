# 最低支持的 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 项目名称（可自定义）
project(MyProject)

# 设置 C++ 标准（根据需要调整，比如 C++11、C++17）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)  # 开启所有警告和额外警告

# 需要告诉编译器.h头文件在哪里 因为只会在cpp文件的相对目录下找 现在分离了两个文件夹会找不到
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    # src/Leetcode347.cpp
    # src/VectorUtils.cpp
    # src/TreeUtils.cpp
    # src/ListUtils.cpp
    # src/SafeQueue.cpp
    # src/ThreadPool.cpp
    src/MaxHeap.cpp
)

# 生成可执行文件（第一个参数是输出文件名，第二个是源文件变量）
add_executable(main ${SOURCES})

# 编译和运行的命令
# mkdir build
# cd build
# cmake -G "MinGW Makefiles" ..
# mingw32-make
# main.exe

# ------------------------------------------下面是编译c文件的-------------------------------------
# # 1. 指定 CMake 最低版本（可选，但推荐）
# cmake_minimum_required(VERSION 3.10)

# # 2. 定义项目名称，指定语言为 C（关键：明确是 C 项目）
# project(HelloC C)

# # 3. 可选：指定 C 标准版本（比如 C99、C11）
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON) # 强制使用指定的 C 标准

# # 4. 添加可执行文件：第一个参数是可执行文件名，第二个是源码文件
# add_executable(main src/memmove.c)

# # 编译和运行的命令
# # mkdir build
# # cd build
# # cmake ..
# # cmake --build .