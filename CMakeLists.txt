PROJECT(Kovel)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)

SET(CMAKE_CXX_STANDARD 11)

OPTION(HAIKU_UI "Use Haiku native API" OFF)
OPTION(WX_UI "Use wxWidgets API" OFF)

FILE(GLOB CORE_SRC "core/*.cpp")

IF(HAIKU_UI)
	FILE(GLOB UI_SRC "ui/haiku/*.cpp")
ENDIF()

IF(WX_UI)
	FILE(GLOB UI_SRC "ui/wx/*.cpp")
ENDIF()

FILE(GLOB GL_SRC "ui/gl/*.cpp")
FILE(GLOB EXPORT_SRC "exporter/*.cpp")
FILE(GLOB CLI_SRC "cli/*.cpp")

SET(KOVEL_SRC ${CORE_SRC} ${UI_SRC} ${GL_SRC} ${EXPORT_SRC})
IF(WIN32)
	LIST(APPEND KOVEL_SRC "resources/kovel.rc")
ENDIF()

ADD_SUBDIRECTORY(libbson)

INCLUDE_DIRECTORIES("libbson/src/bson")
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/libbson/src/bson")

ADD_EXECUTABLE(Kovel ${KOVEL_SRC})
ADD_EXECUTABLE(kovelcli ${CLI_SRC} ${CORE_SRC})

TARGET_LINK_LIBRARIES(Kovel bson_static)
TARGET_LINK_LIBRARIES(kovelcli bson_static)

FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIRS})

IF(HAIKU_UI)
	TARGET_LINK_LIBRARIES(Kovel be root tracker ${OPENGL_LIBRARIES})
	ADD_CUSTOM_COMMAND(TARGET Kovel COMMAND rc -o kovel.rsrc ${CMAKE_CURRENT_SOURCE_DIR}/resources/kovel.rdef COMMENT "Compiling resources")
	ADD_CUSTOM_COMMAND(TARGET Kovel COMMAND xres -o Kovel kovel.rsrc COMMENT "Adding resources to executable")
	ADD_CUSTOM_COMMAND(TARGET Kovel COMMAND mimeset --all Kovel COMMENT "Adjusting MIME types")
	# Apply icon and Haiku metadata
ENDIF()

IF(WX_UI)
	FIND_PACKAGE(wxWidgets COMPONENTS core base gl adv)
	INCLUDE_DIRECTORIES(${wxWidgets_INCLUDE_DIR})
	INCLUDE( "${wxWidgets_USE_FILE}" )
	TARGET_LINK_LIBRARIES(Kovel ${wxWidgets_LIBRARIES} ${OPENGL_LIBRARIES})
ENDIF()
