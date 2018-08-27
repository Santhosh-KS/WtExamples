#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WText>
#include <memory>

using namespace Wt;

class HeaderApplication : public WApplication
{
public:
  HeaderApplication(const WEnvironment& env);

private:
  std::unique_ptr<WContainerWidget> HeaderDiv;
  std::unique_ptr<WContainerWidget> HeaderTextDiv;
  std::unique_ptr<WText> HeaderText;
};

HeaderApplication::HeaderApplication(const WEnvironment& env)
  : WApplication(env),
  HeaderDiv(new Wt::WContainerWidget(root())),
  HeaderTextDiv(new Wt::WContainerWidget(root())),
  HeaderText(new Wt::WText("spookfish"))
{
  useStyleSheet(Wt::WLink("styleSheet.css"));
  HeaderDiv->setId("header");
  HeaderTextDiv->setId("h3");
  HeaderTextDiv->addWidget(HeaderText.get());
  HeaderDiv->addWidget(HeaderTextDiv.get());
}


WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new HeaderApplication(env);
}

int main(int argc, char **argv)
{
  /*
   * Your main method may set up some shared resources, but should then
   * start the server application (FastCGI or httpd) that starts listening
   * for requests, and handles all of the application life cycles.
   *
   * The last argument to WRun specifies the function that will instantiate
   * new application objects. That function is executed when a new user surfs
   * to the Wt application, and after the library has negotiated browser
   * support. The function should return a newly instantiated application
   * object.
   */
  return WRun(argc, argv, &createApplication);
}

