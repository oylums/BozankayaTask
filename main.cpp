#include "Application.hpp"
#include "AppMessages.hpp"


int main(int argc, char *argv[])
{

    Application app(argc,argv);


    AppMessages::installHandler();
    app.initCommon();
    app.init();


    int exitCode = app.exec();

    qInfo() << "App closed successfully " << exitCode;

    return exitCode;
}
