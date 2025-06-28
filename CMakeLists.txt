# CMakeList.txt : CMake project for data-structures-and-algorithms, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (dsa LANGUAGES CXX)

option(CODE_TESTING "Enable code testing" ON)
option(CODE_COVERAGE "Enable coverage reporting" ON)

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
