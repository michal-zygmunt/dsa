# CMakeList.txt : CMake project for data-structures-and-algorithms, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.27)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (dsa LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

# library interface for templates
add_library(dsa INTERFACE)
target_include_directories(dsa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# library interface for tests
add_library(dsa_testing INTERFACE)
target_link_libraries(dsa_testing INTERFACE dsa)


option(ENABLE_WARNINGS "Enable strict compiler flags" ON)
option(DOCS_ENABLED "Enable documentation generation" ON)
option(CODE_TESTING "Enable code testing" ON)
option(CODE_COVERAGE "Enable coverage reporting" ON)


if(ENABLE_WARNINGS)
	message(STATUS "Strict compiler flags option enabled")

	if(MSVC) # MSVC / MS Clang
		message(STATUS "Using strict MSVC / MSVC-Clang flags")
		target_compile_options(dsa_testing INTERFACE
			/W4
			/sdl
			/GS
			/WX
			/RTC1 # /RTCs /RTSu
			/diagnostics:column
			/diagnostics:caret
			/utf-8
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
			target_compile_options(dsa_testing INTERFACE
				-Wuseless-cast
				-Wduplicated-cond
				-Wduplicated-branches 
				-fdiagnostics-color=always
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
		else()
			message(WARNING "Code coverage only supported with Clang")
		endif()
	endif()
	
	include (CTest)
	add_subdirectory(tests)
endif()
