# CMakeList.txt : CMake project for data-structures-and-algorithms, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.27)

project (dsa LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

# library interface for templates
add_library(dsa INTERFACE)
target_include_directories(dsa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# library interface for tests
add_library(dsa_testing INTERFACE)
target_link_libraries(dsa_testing INTERFACE dsa)


option(ENABLE_WARNINGS "Enable strict compiler flags" ON)
option(ENABLE_SANITIZERS "Enable sanitizers ASan/UBSan" ON)
option(ENABLE_CLANG_TIDY "Enable clang-tidy static code analysis" OFF)
option(DOCS_ENABLED "Enable documentation generation" ON)
option(CODE_TESTING "Enable code testing" ON)
option(CODE_COVERAGE "Enable coverage reporting" ON)


if(ENABLE_CLANG_TIDY)
	message(STATUS "Static analysis with clang-tidy option enabled")

	find_program(CLANG_TIDY_EXE NAMES clang-tidy)
	
	if(CLANG_TIDY_EXE)
		message(STATUS "clang-tidy found " ${CLANG_TIDY_EXE})
		set(CMAKE_CXX_CLANG_TIDY
			"${CLANG_TIDY_EXE}"
			"--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
		)
	else()
		message(WARNING "clang-tidy not found")
	endif()
endif()


if(ENABLE_CLANG_TIDY)
	message(STATUS "Static analysis with clang-tidy option enabled")

	find_program(CLANG_TIDY_EXE NAMES clang-tidy)
	
	if(CLANG_TIDY_EXE)
		message(STATUS "clang-tidy found " ${CLANG_TIDY_EXE})
		if(MSVC)
			# /EHs standard c++ stack unwinding, catches c++ exceptions when using catch(...) syntax.
			# /EHc functions declared as extern c never throw a c++ exception.
			# option prevents clang-tools error "cannot use 'throw' with exceptions disabled"
			set(CLANG_TIDY_EXTRA_ARGS "--extra-arg=/EHsc")
		else()
			set(CLANG_TIDY_EXTRA_ARGS "")
		endif()
		set(CMAKE_CXX_CLANG_TIDY
			"${CLANG_TIDY_EXE}"
			"--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
			${CLANG_TIDY_EXTRA_ARGS}
		)
	else()
		message(WARNING "clang-tidy not found")
	endif()
endif()


if(MSVC AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT ENABLE_SANITIZERS)
	message(STATUS "Hot Reload for MSVC compiler enabled")
	# Enable Hot Reload for MSVC compilers if supported:
	# - MSVC-Clang compiler ABI is incompatible
	# - /ZI and /fsanitize=address options are incompatible, flag conflict generate error code D8016
	if (POLICY CMP0141)
	  cmake_policy(SET CMP0141 NEW)
	  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT 
		"$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,"
		"$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
	  )
	endif()
endif()


if(ENABLE_WARNINGS)
	message(STATUS "Strict compiler flags option enabled")

	if(MSVC) # MSVC / MS Clang
		message(STATUS "Using strict MSVC / MSVC-Clang flags")
		target_compile_options(dsa_testing INTERFACE
			/W4
			/sdl
			/GS
			/WX
			/diagnostics:column
			/diagnostics:caret
			/utf-8
			# use runtime check errors only for Debug config
			$<$<CONFIG:Debug>: /RTC1> # /RTCs /RTSu
		)
		# MSVC specific flags
		if(MSVC AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
			target_compile_options(dsa_testing INTERFACE
				/permissive-
				/Zc:__cplusplus
				/Zc:preprocessor
				/MP
			)
		endif()
	else() # GCC / Clang
		target_compile_options(dsa_testing INTERFACE
			-Wall
			-Wextra
			-Wpedantic
			-Werror
			-Wconversion
			-Wsign-conversion
			-Wshadow
			-Wformat=2
			-Wnon-virtual-dtor
			-Wold-style-cast
			-Wcast-align
			-pipe
		)
		# GCC specific flags
		if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			message(STATUS "Using strict GNU flags")
			set (target_options -fdiagnostics-color=always)
				# prevents generation of clang-diagnostic-unknown-warning-option
			if(NOT ENABLE_CLANG_TIDY)
			list(APPEND target_options
					-Wuseless-cast
					-Wduplicated-cond
					-Wduplicated-branches 
			)
			endif()
			target_compile_options(dsa_testing INTERFACE
				${target_options}
			)
		# Clang specific flags
		else(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
			message(STATUS "Using strict Clang flags")
			target_compile_options(dsa_testing INTERFACE
				-Wunreachable-code
				-Wimplicit-fallthrough
				-Wmissing-declarations
				-fcolor-diagnostics
			)
		endif()

		target_link_options(dsa_testing INTERFACE
			-Wl,--as-needed
			-Wl,--no-undefined
		)

		# additional security flags
		target_compile_options(dsa_testing INTERFACE
			-fstack-protector-strong
			-D_FORTIFY_SOURCE=2
			-fPIC
		)
		target_link_options(dsa_testing INTERFACE
			-Wl,-z,relro
			-Wl,-z,now
		)
	endif()
endif()


if(ENABLE_SANITIZERS)
	message(STATUS "Sanitizers option enabled")
	if(MSVC)
		# MSVC specific flags
		if(MSVC AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
			# MSVC feature
			target_compile_options(dsa_testing INTERFACE
				# use sanitizer only for Debug config
				$<$<CONFIG:Debug>: /fsanitize=address>
			)
			# require MSVC-Clang installation
			find_program(CLANGXX_PATH clang++)
			if(CLANGXX_PATH)
			target_compile_options(dsa_testing INTERFACE
				/fsanitize=fuzzer
			)
			endif()

			if(CLANGXX_PATH)
				message(STATUS "Using ASan / Fuzzer sanitizer MSVC / MSVC-Clang")
			else()
				message(STATUS "Using ASan sanitizer MSVC")
			endif()
		else()
			message(STATUS "Using sanitizer for MSVC-Clang not supported")
			# MSVC installer do not provide clang_rt.asan_dynamic-x86_64.lib and clang_rt.asan_dynamic-x86_64.dll
		endif()
	else()
		message(STATUS "Using ASan / UBSan sanitizer Clang / GCC")
		target_compile_options(dsa_testing INTERFACE
			-fsanitize=address,undefined
			-fno-omit-frame-pointer)
		target_link_options(dsa_testing INTERFACE
			-fsanitize=address,undefined)
	endif()
endif()


if(DOCS_ENABLED)
	message(STATUS "Documentation generation enabled")
	
	find_package(Doxygen REQUIRED dot)

	if(Doxygen_FOUND)
		doxygen_add_docs(dsa_docs
		ALL USE_STAMP_FILE
		COMMENT "Generating documentation with custom Doxyfile and dot"
		CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
	else()
		message(WARNING "Doxygen and GraphViz required for code generation")
	endif()

endif()


if(CODE_TESTING)
	message(STATUS "Code testing enabled")

	if(CODE_COVERAGE)
		if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
			message(STATUS "Building with code coverage flags for Clang")
			target_compile_options(dsa_testing INTERFACE
				-fprofile-instr-generate
				-fcoverage-mapping
			)
			target_link_options(dsa_testing INTERFACE
				-fprofile-instr-generate
			)
		elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			message(STATUS "Building with code coverage flags for GCC")
			set(target_options
				-coverage # -fprofile-arcs -ftest-coverage
				-fno-inline
				-fno-elide-constructors
				-O0
				#-O1 # flag prevents mismatch exception tag error when generating report with lcov
				-g
			)
			# prevents generation of clang-diagnostic-error
			if(NOT ENABLE_CLANG_TIDY)
				list(APPEND target_options -fprofile-abs-path)
			endif()
			target_compile_options(dsa_testing INTERFACE
				${target_options}
			)
			target_link_options(dsa_testing INTERFACE
				-coverage # -fprofile-arcs -ftest-coverage
			)
		else()
			message(WARNING "Code coverage only supported with Clang and GCC")
		endif()
	endif()
	
	include (CTest)
	add_subdirectory(tests)
endif()
