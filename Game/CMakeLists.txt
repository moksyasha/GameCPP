# CMakeList.txt: проект CMake для Game; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Game   "Controller.cpp" "View.cpp" "View.h" "Model.cpp" "Model.h" "main.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
