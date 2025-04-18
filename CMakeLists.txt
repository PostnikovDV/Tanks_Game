cmake_minimum_required(VERSION 3.30.1 FATAL_ERROR)

set(PROJECT_NAME Tanks_Game)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
	src/Renderer/Texture2D.h
	src/Renderer/Texture2D.cpp
	src/Renderer/Sprite.h
	src/Renderer/Sprite.cpp
	src/Renderer/VertexBuffer.h
	src/Renderer/VertexBuffer.cpp
	src/Renderer/IndexBuffer.h
	src/Renderer/IndexBuffer.cpp
	src/Renderer/VertexArray.h
	src/Renderer/VertexArray.cpp
	src/Renderer/VertexBufferLayout.h
	src/Renderer/VertexBufferLayout.cpp
	src/Renderer/Renderer.h
	src/Renderer/Renderer.cpp
	src/Renderer/SpriteAnimator.cpp
	src/Renderer/SpriteAnimator.h

	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h
	src/Resources/stb_image.h

	src/Game/Game.h
	src/Game/Game.cpp
	src/Game/Level.cpp
	src/Game/Level.h

	src/Game/GameObject/Tank.h
	src/Game/GameObject/Tank.cpp
	src/Game/GameObject/IGameObject.h
	src/Game/GameObject/IGameObject.cpp
	src/Game/GameObject/BrickWall.cpp
	src/Game/GameObject/BrickWall.h
	src/Game/GameObject/BetonWall.cpp
	src/Game/GameObject/BetonWall.h
	src/Game/GameObject/Tree.cpp
	src/Game/GameObject/Tree.h
	src/Game/GameObject/Ice.cpp
	src/Game/GameObject/Ice.h
	src/Game/GameObject/Water.cpp
	src/Game/GameObject/Water.h
	src/Game/GameObject/Eagle.cpp
	src/Game/GameObject/Eagle.h
	src/Game/GameObject/Border.cpp
	src/Game/GameObject/Border.h

	src/System/Timer.cpp
	src/System/Timer.h

	src/Physics/PhysicsEngine.cpp
	src/Physics/PhysicsEngine.h
	)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL "" FORCE )

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)

include_directories(external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)




