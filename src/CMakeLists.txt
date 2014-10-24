#PicGrabber
# add the executable
add_executable(${OutputName}
	main.cpp
)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${OutputName} ${OpenCV_LIBS})

# add the install targets
install (TARGETS ${OutputName} RUNTIME DESTINATION ${OutputName})
