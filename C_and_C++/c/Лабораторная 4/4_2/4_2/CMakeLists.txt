file( GLOB SRCS *.c )
set(CMAKE_C_FlAGS "-std=c89-pedantic-errors")
add_executable( c ${SRCS} )
