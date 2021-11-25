# CMakeList.txt: GraphLearning 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (GraphLearning "GraphLearning.cpp" "GraphLearning.h" "MatrixGraph_withoutWeight.h" "MatrixGraph_withWeight.h" "Prim_undirected.h" "Prim_directed.h" "Dijkstra.h" "Dijkstra_Pro.h" "MetroProject_v1.0.h")

# TODO: 如有需要，请添加测试并安装目标。
