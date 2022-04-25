#[[
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  This Source Code Form is "Incompatible With Secondary Licenses", as
  defined by the Mozilla Public License, v. 2.0.
]]

macro(add_compilation_test)
	cmake_parse_arguments(COMP_TEST "" "NAME;MAIN;FAIL" "" ${ARGN})
	add_library("${COMP_TEST_NAME}_${COMP_TEST_MAIN}" OBJECT EXCLUDE_FROM_ALL
		"${COMP_TEST_NAME}/impl.cpp"
		"${COMP_TEST_NAME}/${COMP_TEST_MAIN}.cpp"
	)
	target_link_libraries("${COMP_TEST_NAME}_${COMP_TEST_MAIN}" PRIVATE pimpl)
	if (DEFINED COMP_TEST_FAIL)
		set(COMP_TEST_EXPECTED "fails")
	else()
		set(COMP_TEST_EXPECTED "compiles")
	endif()
	add_test(
		NAME "${COMP_TEST_EXPECTED}_${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
		COMMAND "${CMAKE_COMMAND}"
			--build .
			--clean-first
			--target "${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
			--config "$<CONFIGURATION>"
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)
	if (DEFINED COMP_TEST_FAIL)
	set_tests_properties("${COMP_TEST_EXPECTED}_${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
		PROPERTIES
			WILL_FAIL TRUE
			PASS_REGULAR_EXPRESSION "${COMP_TEST_FAIL}"
	)
	endif()
endmacro()

macro(add_runtime_test)
	cmake_parse_arguments(COMP_TEST "" "NAME;MAIN" "" ${ARGN})
	add_executable("${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
		"${COMP_TEST_NAME}/impl.cpp"
		"${COMP_TEST_NAME}/${COMP_TEST_MAIN}.cpp"
	)
	target_link_libraries("${COMP_TEST_NAME}_${COMP_TEST_MAIN}" PRIVATE pimpl)
	add_test(
		NAME "runs_${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
		COMMAND "${COMP_TEST_NAME}_${COMP_TEST_MAIN}"
	)
endmacro()

add_runtime_test(NAME def_constructable MAIN is_constructable)

add_runtime_test(NAME no_features MAIN is_destructable)
add_runtime_test(NAME no_features MAIN is_moveable)
add_compilation_test(NAME no_features MAIN not_def_constructible FAIL "attempting to reference a deleted function")

add_compilation_test(NAME no_instantiations MAIN is_compiling)

