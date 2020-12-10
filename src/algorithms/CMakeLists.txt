macro(createAlgorithm name)
    add_library(${name} ${name}.cpp ${name}.hpp)
    target_compile_features(${name} PUBLIC cxx_std_11)

    install(TARGETS ${name} DESTINATION lib)
    install(FILES ${name}.h DESTINATION include)

    message("--Created Algorithm: " ${name})
endmacro(createAlgorithm)

createAlgorithm(mcts)