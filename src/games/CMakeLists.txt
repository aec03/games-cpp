macro (createGame game)
    add_executable(
        ${game}
        ./${game}/${game}.cpp
        ./${game}/${game}Board.cpp
    )
    target_include_directories(${game} PUBLIC ../algorithms)
    target_link_libraries(${game} PRIVATE mcts)
    message("--Creating Game: " ${game})
endmacro(createGame)

createGame(connectFour)