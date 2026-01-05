# DSA - Data Structures and Algorithms

[![CI](https://github.com/michal-zygmunt/dsa/actions/workflows/ci.yml/badge.svg)](https://github.com/michal-zygmunt/dsa/actions/workflows/ci.yml) &nbsp; [![codecov](https://codecov.io/github/michal-zygmunt/dsa/graph/badge.svg?token=T26A93WPMR)](https://codecov.io/github/michal-zygmunt/dsa) &nbsp; [![Documentation](https://img.shields.io/badge/docs-Doxygen-blue?style=flat)](https://michal-zygmunt.github.io/dsa/)

## Project Description

An educational project focused on reimplementing selected data structures
and algorithms from C++ Standard Template Library using C++20.
The primary goal is to gain deeper understanding of STL design decisions,
implementation trade-offs, and their impact on usability.

### Project features:
- Cross-platform, vendor-independent library compatible with GCC, Clang and MSVC
- Automated unit testing and continuous integration using GitHub Actions
- Code coverage reporting to assess test completeness
- Generation of easily browsable documentation using Doxygen

## Implemented Containers

The following containers are implemented with an STL-like interface,
including iterators and compatibility with standard algorithms
where applicable.

### Sequence Containers

- `dsa::Array<T>`
- `dsa::ForwardList<T>`
- `dsa::List<T>`
- `dsa::Vector<T>`

#### Notes on `dsa::Vector<bool>`

> This template intentionally does not implement a bit-packed
> specialization for `bool`, as found in `std::vector<bool>`.
> The standard container's specialization breaks reference semantics
> and replaces `bool&` with proxy objects.
> `dsa::Vector<bool>` behaves like a regular container,
> without bit-packing. This design choice prioritizes correctness
> and predictable semantics over memory optimization.

### Container Adaptors

- `dsa::Stack<T>`
- `dsa::Queue<T>`

## Requirements

### Required

- CMake (>= 3.27) and CTest to build and run tests
- C++20-compatible compiler (GCC / Clang / MSVC)

### Optional
- Doxygen and Graphviz (dot) to generate documentation locally
- Clang-tidy to check code quality and application of best practices
- Python 3 and WSL/Linux tools to generate code coverage reports locally

Adding CMake configuration options can be used to disable features that
are not available on the local machine and suppress related warnings.
The `CMakeLists.txt` file contains a list of supported flags.
For example, passing `-DDOCS_ENABLED=OFF` flag during the initial
CMake configuration disables documentation generation if the required tools
are not available.

## Build and Test Instructions 

Execute the following commands inside project repository to build and run tests
on your local system:

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release
```

Additional CMake configuration flags can be passed during the initial
configuration step to disable optional features if they are not available
on your local system.

Unit tests compare output of various operations on implemented containers
with output from STL containers.

## Usage Example

```cpp
#include "dsa/vector.h"

#include <iostream>
#include <numeric>

int main()
{
	dsa::Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	for (const auto& item : vec)
	{
		std::cout << item << "\n";
	}

	const int sum = std::accumulate(vec.begin(), vec.end(), 0);
	std::cout << "sum: " << sum << "\n";
}
```

## License Information

Copyright (c) 2025 Michal Zygmunt

The project is distributed under the MIT License.

## Author

Michal Zygmunt

[GitHub](https://github.com/michal-zygmunt) | [LinkedIn](https://www.linkedin.com/in/michal-zygmunt/)
