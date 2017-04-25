file( GLOB CSources *.c )
add_library( flist ${CSources} )
install( TARGETS flist DESTINATION lib )
