set(SOURCES
        main.cpp
        analizadorLex.cpp
        analizadorSint.cpp
        arbolSint.cpp
        compilador.cpp
)

set(HEADERS include)

add_executable(PROYECTO-FINAL ${SOURCES} ${HEADERS})

target_include_directories(PROYECTO-FINAL PUBLIC include)