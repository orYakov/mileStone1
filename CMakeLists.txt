cmake_minimum_required(VERSION 3.13)
project(mileStone1)

set(CMAKE_CXX_STANDARD 14)

add_executable(mileStone1 main.cpp Command.h Parser.cpp Parser.h Expression.h Num.cpp Num.h Plus.cpp Plus.h BinaryExpression.cpp BinaryExpression.h Minus.cpp Minus.h Div.cpp Div.h Mul.cpp Mul.h ShuntingYard.cpp ShuntingYard.h Lexer.cpp Lexer.h)