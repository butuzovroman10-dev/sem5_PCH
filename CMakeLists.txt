cmake_minimum_required(VERSION 3.10)
project(it_company_collection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(it_company_collection
    main.cpp
    IWorkable.h
    Employee.h
    Developer.h
    Manager.h
    Tester.h
    MyContainer.h
)

target_include_directories(it_company_collection PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})