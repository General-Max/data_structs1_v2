cmake_minimum_required(VERSION 3.21)
project(data_structrs_wet1_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(data_structrs_wet1_main
        AVLTree.h
        BinNode.h
        Deque.h
        DoubleNode.h
        ListNode.h
        main.cpp
        Node.h
        Player.cpp
        Player.h
        sortingTreeMethods.cpp
        sortingTreeMethods.h
        SortTeamById.cpp
        SortTeamById.h
        Team.cpp
        Team.h
        twoWayList.h
        wet1util.h
        worldcup23a1.cpp
        worldcup23a1.h)
