cmake_minimum_required(VERSION 3.10)
project(TexasTests)

add_executable(stbi_test "stbi_test.cpp")
target_include_directories(stbi_test PRIVATE external)

add_subdirectory("D:/Personal/Texas" Texas)
target_link_libraries(stbi_test PRIVATE Texas)


	# Remove data folder from target binary directory
	add_custom_command(
		TARGET stbi_test POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E remove_directory
		$<TARGET_FILE_DIR:stbi_test>/data)

	# Copy data directory from source folder to build folder
	add_custom_command(
		TARGET stbi_test POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/data
		$<TARGET_FILE_DIR:stbi_test>/data/)