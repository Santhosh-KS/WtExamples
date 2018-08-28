#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WBootstrapTheme>

#include <Wt/WText>
#include <Wt/WLink>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <memory>

using namespace Wt;

class HeaderApplication : public WApplication
{
public:
  HeaderApplication(const WEnvironment& env);

private:
  std::unique_ptr<Wt::WContainerWidget> HeaderDiv;
  std::unique_ptr<Wt::WContainerWidget> HeaderDivTextDiv;
  std::unique_ptr<Wt::WText> HeaderText;
  std::unique_ptr<Wt::WContainerWidget> MainDiv;
  std::unique_ptr<Wt::WContainerWidget> MainLeftDiv;
  std::unique_ptr<Wt::WContainerWidget> MainRightDiv;
  std::unique_ptr<Wt::WContainerWidget> SearchDiv;
  std::unique_ptr<Wt::WContainerWidget> SearchDivLineEditDiv;
  std::unique_ptr<Wt::WLineEdit> SearchLineEdit;
  std::unique_ptr<Wt::WContainerWidget> SearchDivPlayButtonDiv;
  std::unique_ptr<Wt::WPushButton> PlayButton;


  std::unique_ptr<Wt::WBootstrapTheme> Theme;
};

HeaderApplication::HeaderApplication(const WEnvironment& env)
  : WApplication(env),
  Theme(std::make_unique<Wt::WBootstrapTheme>()),
  MainDiv(std::make_unique<Wt::WContainerWidget>(root())),
  HeaderDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderDivTextDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderText(std::make_unique<Wt::WText>("spookfish")),
  MainLeftDiv(std::make_unique<Wt::WContainerWidget>()),
  MainRightDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDivLineEditDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchLineEdit(std::make_unique<Wt::WLineEdit>("Give me Youtube URL")),
  SearchDivPlayButtonDiv(std::make_unique<Wt::WContainerWidget>()),
  PlayButton(std::make_unique<Wt::WPushButton>("Play"))
{
  Theme->setVersion(Wt::WBootstrapTheme::Version3);
  setTheme(Theme.get());

  useStyleSheet(Wt::WLink("styleSheet.css"));
  //useStyleSheet(Wt::WLink("resources/main.css"));
  useStyleSheet(Wt::WLink("resources/themes/bootstrap/3/bootstrap.min.css"));

  HeaderDiv->setId("header");
  HeaderDiv->setStyleClass(Wt::WString::fromUTF8(""));
  HeaderDivTextDiv->setId("h3");
  HeaderDivTextDiv->addWidget(HeaderText.get());
  HeaderDiv->addWidget(HeaderDivTextDiv.get());

  MainLeftDiv->setId("main_left");
  MainRightDiv->setId("main_right");
  //SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-6 col-xs-6 col-lg-6 col-sm-6"));
  SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-6"));
  SearchDiv->setStyleClass(Wt::WString::fromUTF8("input-group"));
  //SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-12 input-group"));
  SearchLineEdit->setStyleClass(Wt::WString::fromUTF8("form-control"));
  SearchLineEdit->setFocus(true);
  SearchDivPlayButtonDiv->setStyleClass(Wt::WString::fromUTF8("input-group-btn"));
  SearchDivPlayButtonDiv->setInline(1);
  PlayButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));

  SearchDivLineEditDiv->addWidget(SearchLineEdit.get());
  SearchDivPlayButtonDiv->addWidget(PlayButton.get());

  SearchDiv->addWidget(SearchDivLineEditDiv.get());
  SearchDiv->addWidget(SearchDivPlayButtonDiv.get());
  MainLeftDiv->addWidget(SearchDiv.get());

  MainDiv->addWidget(HeaderDiv.get());
  MainDiv->addWidget(MainRightDiv.get());
  MainDiv->addWidget(MainLeftDiv.get());
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

