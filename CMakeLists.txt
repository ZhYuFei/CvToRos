cmake_minimum_required(VERSION 3.5)
project(cv_to_ros)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
ament_auto_find_build_dependencies()

include_directories(include)

file(GLOB_RECURSE CPP_SOURCE_FILES src/*.*)
ament_auto_add_library(${PROJECT_NAME} SHARED
  ${CPP_SOURCE_FILES}
)

add_library(img_projector SHARED
  src/img_projector.cpp)
target_compile_definitions(img_projector
  PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(img_projector
  "rclcpp"
  "rclcpp_components"
  "std_msgs"
  "sensor_msgs"
  "OpenCV"
  "cv_bridge")
rclcpp_components_register_nodes(img_projector "cv_to_ros::projector")
set(node_plugins "${node_plugins}cv_to_ros::projector;$<TARGET_FILE:img_projector>\n")

ament_environment_hooks("${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}")

set(libs
img_projector
SectorFinder
SectorPredict)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(libs
    "-Wl,--no-as-needed"
    ${libs}
    "-Wl,--as-needed")
endif()

install(TARGETS
  img_projector
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(DIRECTORY
  example
  DESTINATION share/${PROJECT_NAME}
)

ament_package()