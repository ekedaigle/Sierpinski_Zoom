add_library(SOIL SHARED SOIL.c image_DXT.c image_helper.c stb_image_aug.c)
target_link_libraries(SOIL ${OPENGL_LIBRARIES})

if(APPLE)
    FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation)
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    target_link_libraries(SOIL ${COREFOUNDATION_LIBRARY})
endif(APPLE)
