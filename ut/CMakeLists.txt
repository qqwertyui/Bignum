set(INPUT_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated_input/)
file(COPY ${INPUT_DATA_DIR}/add.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/sub.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/mul.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/div.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/mod.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(TestBignumOperations TestBignumOperations.cpp)
target_link_libraries(TestBignumOperations bignum)
target_link_options(TestBignumOperations PUBLIC -static-libstdc++)

add_executable(TestWithGeneratedInput TestWithGeneratedInput.cpp)
target_link_libraries(TestWithGeneratedInput bignum)
target_link_options(TestWithGeneratedInput PUBLIC -static-libstdc++)