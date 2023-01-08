cmake_minimum_required(VERSION 3.14)

Project(Volante 
	VERSION 0.0.1
	DESCRIPTION "Volante para pc"
	LANGUAGES C
)

include(cmake/libopencm3.cmake)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_LINKER_FLAGS} -T${LINKER_FILE}")

add_subdirectory(stm32f103)


#add_subdirectory(src)
