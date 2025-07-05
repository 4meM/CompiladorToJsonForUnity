set(SOURCES
        main.cpp
        analizadores/analizadorLex.cpp
        analizadores/analizadorSint.cpp
        analizadores/analizadorSem.cpp
        compilador.cpp
        generadorJson.cpp
)

set(HEADERS include)

add_executable(PROYECTO-FINAL ${SOURCES} ${HEADERS})

target_include_directories(PROYECTO-FINAL PUBLIC include)