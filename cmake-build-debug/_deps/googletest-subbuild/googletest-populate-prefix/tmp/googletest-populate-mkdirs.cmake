# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-src"
  "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-build"
  "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/zix/WinBuntu/JetBrains_IDEs/clion_projects/OOP/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
