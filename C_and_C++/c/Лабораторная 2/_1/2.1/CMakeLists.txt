file( GLOB SRCS *.c *.h )
add_compile_options(--ansi)
add_executable( c ${SRCS} )
