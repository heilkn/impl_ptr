#include(GenerateExportHeader)

macro(add_compilation_test)
	cmake_parse_arguments(COMP_TEST "" "NAME;MAIN" "" ${ARGN})
	add_library("${COMP_TEST_NAME}_${COMP_TEST_MAIN}" OBJECT EXCLUDE_FROM_ALL
		"${COMP_TEST_NAME}/impl.cpp"
		"${COMP_TEST_NAME}/${COMP_TEST_MAIN}.cpp"
	)
	target_link_libraries("${COMP_TEST_NAME}_${COMP_TEST_MAIN}" PRIVATE pimpl)
	add_test(
		NAME "test_${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
		COMMAND "${CMAKE_COMMAND}"
			--build .
			--clean-first
			--target "${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
			--config "$<CONFIGURATION>"
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)
#set_tests_properties("test_${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
#	PROPERTIES
#		WILL_FAIL TRUE
#		PASS_REGULAR_EXPRESSION "foo failed"
#)
endmacro()

macro(add_runtime_test)
	cmake_parse_arguments(COMP_TEST "" "NAME;MAIN" "" ${ARGN})
	add_executable("${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
		"${COMP_TEST_NAME}/impl.cpp"
		"${COMP_TEST_NAME}/${COMP_TEST_MAIN}.cpp"
	)
	target_link_libraries("${COMP_TEST_NAME}_${COMP_TEST_MAIN}" PRIVATE pimpl)
	add_test(
		NAME "${COMP_TEST_NAME}_${COMP_TEST_MAIN}_runs"
		COMMAND "${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
	)
endmacro()

add_runtime_test(NAME def_constructable MAIN is_constructable)

add_runtime_test(NAME no_features MAIN is_destructable)
add_runtime_test(NAME no_features MAIN is_moveable)
add_compilation_test(NAME no_features MAIN not_def_constructible)

add_compilation_test(NAME no_instantiations MAIN is_compiling)

