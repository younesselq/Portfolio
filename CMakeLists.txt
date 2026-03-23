cmake_minimum_required(VERSION 3.16)

project(Portfolio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cherche Qt6 Quick
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

# Exécutable principal
qt_add_executable(appPortfolio
    Src/main.cpp
    Src/models/ExperienceModel.hpp
    Src/models/ExperienceModel.cpp
    Src/models/Educationmodel.h
    Src/models/Educationmodel.cpp
    Src/models/ProfileModel.h
    Src/models/ProfileModel.cpp
    Src/models/SkillModel.hpp
    Src/models/Skillmodel.cpp
)

# Module QML
qt_add_qml_module(appPortfolio
    URI Portfolio
    VERSION 1.0
    QML_FILES
        qml/Main.qml

)

# Ajouter les ressources JSON
# Ajouter les fichiers JSON comme ressources Qt
qt_add_resources(appPortfolio "resources"
    PREFIX "/Ressources/data"
    FILES
        Ressources/data/education.json
        Ressources/data/experiences.json
        Ressources/data/profile.json
        Ressources/data/skills.json
)

target_sources(appPortfolio PRIVATE ${APP_RESOURCES})

# Propriétés du bundle (macOS / Windows)
set_target_properties(appPortfolio PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPortfolio
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Lien avec Qt Quick
target_link_libraries(appPortfolio
    PRIVATE Qt6::Quick
)

# Installation
include(GNUInstallDirs)
install(TARGETS appPortfolio
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
