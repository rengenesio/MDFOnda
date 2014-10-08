QT       += core gui opengl

TARGET = MDFonda
TEMPLATE = app

unix{
    LIBS += -lGLU -lglut
}

SOURCES += src/main.cpp\
    src/MainWindow.cpp\
    src/GLDisplay.cpp \
    src/ArcBall.cpp \
    src/RenderController.cpp \
    src/Object3D.cpp \
    src/DirectionalLight.cpp \
    src/Scene3D.cpp \
    src/Wave.cpp \
    src/Vector.cpp \
    src/Point.cpp \
    src/Color.cpp


HEADERS  += src/MainWindow.h\
    src/GLDisplay.h \
    src/ArcBall.h \
    src/RenderController.h \
    src/Object3D.h \
    src/DirectionalLight.h \
    src/Scene3D.h \
    src/Wave.h \
    src/Vector.h \
    src/Point.h \
    src/Color.h \
    src/UIMainWindow.h

FORMS    += 
