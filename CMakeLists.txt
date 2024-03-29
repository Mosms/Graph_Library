cmake_minimum_required(VERSION 3.14)
project(GraphLibrary)

find_package(Git)

set(CMAKE_CXX_STANDARD 17)
include_directories("include")
file(GLOB sources "source/**/*.cpp")
add_library(GraphLibrary ${sources} include/DataStructures/WeightedEdge.h include/DataStructures/WeightedGraph.h source/DataStructures/WeightedEdge.cpp source/DataStructures/WeightedGraph.cpp include/DataStructures/UndirectedGraph.h source/DataStructures/UndirectedGraph.cpp include/DataStructures/UndirectedWeightedGraph.h source/DataStructures/UndirectedWeightedGraph.cpp source/Algorithms/BreadthFirstSearcher.cpp source/Algorithms/DepthFirstSearcher.cpp source/Algorithms/ShortestPaths.cpp include/Algorithms/DijkstraShortestPaths.h source/Algorithms/DijkstraShortestPaths.cpp include/Algorithms/BellmanFordShortestPaths.h source/Algorithms/BellmanFordShortestPaths.cpp source/Algorithms/MultiSourceShortestPaths.cpp include/Algorithms/FloydShortestPaths.h source/Algorithms/FloydShortestPaths.cpp include/Exceptions/GLException.h source/Exceptions/GLException.cpp include/Exceptions/NegativeCycleException.h source/Exceptions/NegativeCycleException.cpp)

add_custom_target(GitTraceAdd
        COMMAND "${GIT_EXECUTABLE}" add -A . --ignore-errors
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_custom_target(GitTraceCommit
        COMMAND "${GIT_EXECUTABLE}"
        commit -q --allow-empty --no-verify -m "compile"
        --author="tracer-ps3-2021 <tracer-ps3-2021@nju.edu.cn>"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_dependencies(GitTraceCommit GitTraceAdd) # Avoid data race
add_dependencies(GraphLibrary GitTraceCommit)
add_custom_command(TARGET GraphLibrary POST_BUILD
        COMMAND "${GIT_EXECUTABLE}"
        commit -q --allow-empty --no-verify -m "compile succeed"
        #--author="tracer-ps3-2021 <tracer-ps3-2021@nju.edu.cn>"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Your custom tests below
add_executable(Test01 tests/01-hello-world.cpp)
target_link_libraries(Test01 GraphLibrary)
