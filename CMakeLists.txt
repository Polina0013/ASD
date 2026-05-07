# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# название проекта
project(Algorithms-and-Data-Structures)

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)               # подхватываем функции, реализованные в файле function.cmake
                                            # для простоты мы объединили наборы команд для создания статической библиотеки
					    			# и для создания исполняемого проекта в отдельные функции

add_subdirectory(lib_easy_example)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_easy_example
add_subdirectory(lib_tvector)                     # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_tvector
add_subdirectory(lib_stack)                       # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_stack
add_subdirectory(lib_queue)                       # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_queue
add_subdirectory(lib_list)                        # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_list
add_subdirectory(lib_doubly_linked_list)          # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_doubly_linked_list
add_subdirectory(lib_skip_list)                   # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_skip_list

add_subdirectory(algorithms)                      # подключаем дополнительный CMakeLists.txt из подкаталога с именем algorithms

add_subdirectory(lib_stack_via_list)              # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_stack_via_list
add_subdirectory(lib_queue_via_list)              # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_queue_via_list

add_subdirectory(lib_dsu)                         # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_dsu
add_subdirectory(maze_on_dsu)                     # подключаем дополнительный CMakeLists.txt из подкаталога с именем maze_on_dsu

add_subdirectory(lib_itable)                      # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_itable
add_subdirectory(lib_table)                       # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_table

add_subdirectory(lib_unsorted_table_on_vector)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_unsorted_table_on_vector
add_subdirectory(lib_unsorted_table_on_list)      # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_unsorted_table_on_list
add_subdirectory(lib_sorted_table_on_vector)      # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_sorted_table_on_vector

add_subdirectory(lib_monom)                       # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_monom
add_subdirectory(lib_polynom)                     # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_polynom

add_subdirectory(lib_binary_tree)                 # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_binary_tree
add_subdirectory(lib_binary_search_tree)          # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_binary_search_tree

add_subdirectory(lib_unsorted_table_on_binary_tree)        # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_unsorted_table_on_binary_tree
add_subdirectory(lib_sorted_table_on_binary_search_tree)   # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_sorted_table_on_binary_search_tree

add_subdirectory(lib_avl_tree)                    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_avl_tree
add_subdirectory(lib_sorted_table_on_avl_tree)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_sorted_table_on_avl_tree

add_subdirectory(lib_heap_on_vector)              # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_heap_on_vector
add_subdirectory(lib_priority_queue)              # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_priority_queue

add_subdirectory(lib_hash_table)                  # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_hash_table
add_subdirectory(lib_chained_hash_table)          # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_chained_hash_table

add_subdirectory(lib_graph)                       # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_graph
add_subdirectory(lib_graph_adjacency_matrix)      # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_graph_adjacency_matrix
add_subdirectory(dijkstras_algorithm_with_vector) # подключаем дополнительный CMakeLists.txt из подкаталога с именем dijkstras_algorithm_with_vector

add_subdirectory(maze_with_path)                  # подключаем дополнительный CMakeLists.txt из подкаталога с именем maze_with_path






add_subdirectory(main)                      # подключаем дополнительный CMakeLists.txt из подкаталога с именем main

option(BTEST "build test?" ON)              # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                                   # если тесты подключены         
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()


