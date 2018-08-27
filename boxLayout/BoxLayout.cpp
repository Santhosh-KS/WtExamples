/*
 * Copyright (C) 2008 Emweb bvba, Heverlee, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <memory>

// c++0x only, for std::bind
// #include <functional>

using namespace Wt;

class BoxApplication : public WApplication
{
public:
  BoxApplication(const WEnvironment& env);

private:
  //WLineEdit *nameEdit_;
  //WText *greeting_;
  std::unique_ptr<Wt::WContainerWidget> h3;
  std::unique_ptr<Wt::WContainerWidget> Header;
  std::unique_ptr<Wt::WContainerWidget> container;
  std::unique_ptr<Wt::WText> question;
  std::unique_ptr<Wt::WLineEdit> nameEdit_;
  std::unique_ptr<Wt::WPushButton> button;
  std::unique_ptr<Wt::WText> greeting_;
  std::unique_ptr<Wt::WText> text;
  std::unique_ptr<Wt::WText> helptext;

  void greet();
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
BoxApplication::BoxApplication(const WEnvironment& env)
  : WApplication(env),
  h3(std::make_unique<Wt::WContainerWidget>(root())),
  Header(std::make_unique<Wt::WContainerWidget>(root())),
  container(std::make_unique<Wt::WContainerWidget>(root())),
  question(std::make_unique<Wt::WText>("<h1>YOur name, Please?<h1>")),
  nameEdit_(std::make_unique<Wt::WLineEdit>()),
  button(std::make_unique<Wt::WPushButton>()),
  helptext(std::make_unique<Wt::WText>("HelpText"))
{
  setTitle("Hello world");                               // application title

  //root()->addWidget(new WText("Your name, please ? "));  // show some text
  //nameEdit_ = new WLineEdit(root());                     // allow text input
  //Wt::WApplication::instance()->useStyleSheet(Wt::WLink("styleSheet.css"));
  useStyleSheet(Wt::WLink("styleSheet.css"));
  Header->setId("header");
  h3->setId("h3");
  container->addWidget(question.get());
  root()->addWidget(new WBreak());                       // insert a line break
  h3->addWidget(helptext.get());
  Header->addWidget(h3.get());
  root()->addWidget(new WBreak());                       // insert a line break
  nameEdit_->setFocus();                                 // give focus
  container->addWidget(nameEdit_.get());

/*  WPushButton *button
    = new WPushButton("Greet me.", root());              // create a button
  button->setMargin(5, Left);                            // add 5 pixels margin
*/
//  WPushButton *button
  //  = new WPushButton();              // create a button
    //= new WPushButton(root());              // create a button
  button->setText(Wt::WString::fromUTF8("Upload"));
  button->setMargin(5, Left);                            // add 5 pixels margin
  container->addWidget(button.get());
  container->addWidget(new Wt::WBreak());


  //root()->addWidget(std::move(button));                       // insert a line break
  //root()->addWidget(new WBreak());                       // insert a line break

  //greeting_ = new WText(root());                         // empty text
  //greeting_ = new WText();                         // empty text
  greeting_ = std::make_unique<Wt::WText>(root());// empty text
  container->addWidget(greeting_.get());
  //root()->addWidget(greeting_.get());

  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */
  //container->hide();
  button->clicked().connect(this, &BoxApplication::greet);

  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */
  nameEdit_->enterPressed().connect
    (boost::bind(&BoxApplication::greet, this));

  /*
   * - using a c++0x lambda:
   */
  // button->clicked().connect(std::bind([=]() {
  //       greeting_->setText("Hello there, " + nameEdit_->text());
  // }));
}

void BoxApplication::greet()
{
  /*
   * Update the text, using text input into the nameEdit_ field.
   */
  greeting_->setText("Hello there, " + nameEdit_->text());
}

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new BoxApplication(env);
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

