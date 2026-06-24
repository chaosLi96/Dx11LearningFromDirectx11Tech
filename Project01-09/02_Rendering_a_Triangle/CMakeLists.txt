cmake_minimum_required(VERSION 3.14)

add_compile_definitions(UNICODE _UNICODE)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

aux_source_directory(. DIR_SRCS)


file(GLOB HEADER_FILES ./*.h)





add_executable(02_Rendering_a_Triangle WIN32 ${DIR_SRCS} ${HEADER_FILES})


target_link_libraries(02_Rendering_a_Triangle d3d11.lib dxgi.lib dxguid.lib D3DCompiler.lib d2d1.lib dwrite.lib winmm.lib)

set_target_properties(02_Rendering_a_Triangle PROPERTIES OUTPUT_NAME "02_Rendering_a_Triangle")

set_target_properties(02_Rendering_a_Triangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(02_Rendering_a_Triangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(02_Rendering_a_Triangle PROPERTIES FOLDER "Project01-09")