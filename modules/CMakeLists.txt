set(MODULES_FILES
    modules.cpp
   )

add_library(modules SHARED ${MODULES_FILES})
install(TARGETS modules LIBRARY DESTINATION lib)

