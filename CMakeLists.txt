# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 2.6)
find_package(Rock)
rock_init(ASN_Viz 0.1)

include($ENV{ESROCOS_CMAKE})

esrocos_init()

rock_standard_layout()
