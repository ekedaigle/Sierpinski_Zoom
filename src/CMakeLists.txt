add_executable(sierpinski_zoom main.cpp sierpinski_carpet.cpp)
target_link_libraries(sierpinski_zoom ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
