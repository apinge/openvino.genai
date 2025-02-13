# Copyright (C) 2023-2025 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

find_package(OpenVINOGenAI REQUIRED
    PATHS
        "${CMAKE_BINARY_DIR}"  # Reuse the package from the build.
        ${OpenVINO_DIR}  # GenAI may be installed alogside OpenVINO.
    NO_CMAKE_FIND_ROOT_PATH
)

function(add_sample_executable target_name)
    add_executable(${target_name} ${target_name}.c)
    set_source_files_properties(${target_name}.c PROPERTIES LANGUAGE C)
    target_link_libraries(${target_name} PRIVATE openvino::genai)
    # set_target_properties(${target_name} PROPERTIES
    #     COMPILE_PDB_NAME ${target_name}
    #     # Ensure out-of-box LC_RPATH on macOS with SIP
    #     INSTALL_RPATH_USE_LINK_PATH ON)
    # install(TARGETS ${target_name}
    #         RUNTIME DESTINATION samples_bin/
    #         COMPONENT samples_bin
    #         EXCLUDE_FROM_ALL)
endfunction()

set (SAMPLE_LIST
    greedy_causal_lm_c)

foreach(sample ${SAMPLE_LIST})
    add_sample_executable(${sample})
endforeach()


# benchmark_genai
include(FetchContent)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# FetchContent_Declare(cxxopts
#     URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.1.1.tar.gz
#     URL_HASH SHA256=523175f792eb0ff04f9e653c90746c12655f10cb70f1d5e6d6d9491420298a08)
# FetchContent_MakeAvailable(cxxopts)

# add_executable(greedy_causal_lm_c greedy_causal_lm.c)
# #target_link_libraries(greedy_causal_lm_c PRIVATE openvino::genai cxxopts::cxxopts)
# target_link_libraries(greedy_causal_lm_c PRIVATE openvino::genai)
# set_target_properties(greedy_causal_lm_c PROPERTIES
#     COMPILE_PDB_NAME greedy_causal_lm_c
#     # Ensure out of box LC_RPATH on macOS with SIP
#     INSTALL_RPATH_USE_LINK_PATH ON)

# install(TARGETS greedy_causal_lm_c
#         RUNTIME DESTINATION samples_bin/
#         COMPONENT samples_bin
#         EXCLUDE_FROM_ALL)