link_directories(${LIB_BINARY_DIR}/lib)
add_executable(sierpinski_zoom main.cpp sierpinski_carpet.cpp sierpinski_carpet.h)
target_link_libraries(sierpinski_zoom ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
