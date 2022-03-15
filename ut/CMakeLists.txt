function(add_ut target_name files libraries)
  add_executable(${target_name} ${files})
  target_link_libraries(${target_name} ${libraries})
endfunction()

set(INPUT_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated_input/)
file(COPY ${INPUT_DATA_DIR}/add.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/sub.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/mul.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/div.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${INPUT_DATA_DIR}/mod.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_ut(TestBignumOperations TestBignumOperations.cpp bignum)
add_ut(TestWithGeneratedInput TestWithGeneratedInput.cpp bignum)