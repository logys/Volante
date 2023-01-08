include_directories(inc)

file(GLOB C_SOURCE
    main.c
)

set_source_files_properties(${C_SOURCE}
    PROPERTIES COMPILE_FLAGS ${STM32_DEFINES}
)

add_executable(${PROJECT_NAME}.elf
    ${C_SOURCE}
    ${EXTERNAL_EXECUTABLES}
)

if (EXTERNAL_DEPENDENCIES)
    add_dependencies(${PROJECT_NAME}.elf
        ${EXTERNAL_DEPENDENCIES}
    )
endif()

if (EXTERNAL_LIBS)
    target_link_libraries(${PROJECT_NAME}.elf
        ${EXTERNAL_LIBS}
    )
endif()

add_custom_target(size
	COMMAND arm-none-eabi-size -G ${PROJECT_NAME}.elf
	DEPENDS ${PROJECT_NAME}.elf)

add_custom_target(flash
	COMMAND arm-none-eabi-objcopy -Obinary ${PROJECT_NAME}.elf 
	${PROJECT_NAME}.bin && st-flash write ${PROJECT_NAME}.bin 0x8000000
	DEPENDS ${PROJECT_NAME}.elf)
