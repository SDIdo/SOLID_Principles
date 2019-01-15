cmake_minimum_required(VERSION 3.12)
project(projectpart2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -std=c++11 -pthread")

add_executable(projectpart2 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.h StringReverser.cpp StringReverser.h Main.h Algos/State.h Algos/Searchable.h Algos/Entry.h Algos/MatrixGraph.h Algos/MyClientHandler.h Algos/Searcher.h Algos/IO.cpp Algos/IO.h Algos/SearcherSolver.h Algos/BFS.h Algos/DFS.h Algos/AStar.h Algos/BestFirstSearch.h Algos/MyParallelServer.h Algos/MyParallelServer.cpp Algos/MatrixTester.cpp Algos/MatrixTester.h)