cmake_minimum_required (VERSION 2.6)

project (Homework4)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")


SET(
	LIB_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/CompileError1.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/CompileError2.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Demo.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DummyChoosers.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DummyGuessers.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/play.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SmartGuesser.cpp
)


SET(
	TESTER_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp 
)

SET(
	DEMO_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Demo.cpp 
)

add_library(PullPgiaLib STATIC ${LIB_SOURCES})

add_executable(tester ${TESTER_SOURCES})

target_link_libraries(tester pthread PullPgiaLib)

add_executable(demo ${DEMO_SOURCES})

target_link_libraries(demo pthread PullPgiaLib)
