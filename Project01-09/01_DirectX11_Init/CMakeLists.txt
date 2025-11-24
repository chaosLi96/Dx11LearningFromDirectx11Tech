cmake_minimum_required(VERSION 3.14)

add_compile_definitions(UNICODE _UNICODE)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

aux_source_directory(. DIR_SRCS)

file(GLOB HEADER_FILES ./*.h)

add_executable(01_DirectX11_Init WIN32 ${DIR_SRCS} ${HEADER_FILES})

target_link_libraries(01_DirectX11_Init d3d11.lib dxgi.lib dxguid.lib D3DCompiler.lib d2d1.lib dwrite.lib winmm.lib)

set_target_properties(01_DirectX11_Init PROPERTIES OUTPUT_NAME "01_DirectX11_Init")

set_target_properties(01_DirectX11_Init PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(01_DirectX11_Init PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(01_DirectX11_Init PROPERTIES FOLDER "Project01-09")