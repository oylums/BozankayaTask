#include "Application.hpp"

int main(int argc, char *argv[])
{

    Application app(argc,argv);

    app.initCommon();
    app.init();

    return app.exec();
}
