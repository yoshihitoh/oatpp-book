#include <iostream>

#include "oatpp-swagger/Controller.hpp"

#include "controller/book_controller.hpp"
#include "app_component.hpp"
#include "logger.hpp"

using namespace std;

static void run()
{
    AppComponent components;

    auto router = components.httpRouter.getObject();

    auto book_controller = BookController::createShared();
    book_controller->addEndpointsToRouter(router);

    auto doc_endpoints = oatpp::swagger::Controller::Endpoints::createShared();
    doc_endpoints->pushBackAll(book_controller->getEndpoints());

    auto swagger_controller = oatpp::swagger::Controller::createShared(doc_endpoints);
    swagger_controller->addEndpointsToRouter(router);

    oatpp::network::server::Server server(components.serverConnectionProvider.getObject(),
                                          components.serverConnectionHandler.getObject());
    OATPP_LOGD("Server", "Running on port %u...", components.serverConnectionProvider.getObject()->getPort());
    server.run();
}

int main(int argc, char** argv)
{
    oatpp::base::Environment::setLogger(new Logger());
    oatpp::base::Environment::init();

    run();

    oatpp::base::Environment::setLogger(nullptr);
    oatpp::base::Environment::destroy();

    return 0;
}
