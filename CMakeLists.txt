cmake_minimum_required(VERSION 3.13)
project(mileStone1)

set(CMAKE_CXX_STANDARD 14)

add_executable(mileStone1 main.cpp Command.h Parser.cpp Parser.h Expression.h Num.cpp Num.h Plus.cpp Plus.h BinaryExpression.cpp BinaryExpression.h Minus.cpp Minus.h Div.cpp Div.h Mul.cpp Mul.h ShuntingYard.cpp ShuntingYard.h Lexer.cpp Lexer.h DefineVarCommand.cpp DefineVarCommand.h SleepCommand.cpp SleepCommand.h MapHolder.cpp MapHolder.h PrintCommand.cpp PrintCommand.h ConditionParser.cpp ConditionParser.h LoopCommand.cpp LoopCommand.h IfCommand.cpp IfCommand.h OpenServerCommand.cpp OpenServerCommand.h DefinitionCommand.cpp DefinitionCommand.h cmake-build-debug/CMakeFiles/mileStone1.dir/ConnectCommand.cpp cmake-build-debug/CMakeFiles/mileStone1.dir/ConnectCommand.h ConnectCommand.cpp ConnectCommand.h)