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


option(DOCS_ENABLED "Enable documentation generation" ON)
option(CODE_TESTING "Enable code testing" ON)
option(CODE_COVERAGE "Enable coverage reporting" ON)


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
		if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

			if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT MATCHES "MSVC")
				message(STATUS "Building with code coverage flags for Clang-MSVC")
			
				add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
				add_link_options(-fprofile-instr-generate)
			endif()

		else()
			message(WARNING "Code coverage only supported with Clang-MSVC")
		endif()
	endif()

	
	include (CTest)
	add_subdirectory(tests)
endif()
