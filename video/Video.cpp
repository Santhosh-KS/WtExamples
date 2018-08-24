#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WImage>
#include <Wt/WLink>
#include <Wt/WText>
#include <Wt/WVideo>
#include <memory>

// c++0x only, for std::bind
// #include <functional>

using namespace Wt;

/*
 * A simple hello world application class which demonstrates how to react
 * to events, read input, and give feed-back.
 */
class VideoApplication : public WApplication
{
public:
  VideoApplication(const WEnvironment& env);

private:
  std::unique_ptr<WContainerWidget> container;
  std::unique_ptr<WVideo> video;
  std::unique_ptr<WText> out;

  void SetText(const std::string str);
};

VideoApplication::VideoApplication(const WEnvironment& env)
  : WApplication(env),
  container(new Wt::WContainerWidget()),
  video(new Wt::WVideo()),
  out(new Wt::WText())
{
  std::string mp4Video = "https://www.webtoolkit.eu/videos/sintel_trailer.mp4";
  std::string ogvVideo = "https://www.webtoolkit.eu/videos/sintel_trailer.ogv";

  std::string poster = "pics/sintel_trailer.jpg";

  //auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();
  //container = std::make_unique<Wt::WContainerWidget>();
  //container = new Wt::WContainerWidget();

  //auto video = container->addWidget(Wt::cpp14::make_unique<Wt::WVideo>());
  //video = container->addWidget(std::make_unique<Wt::WVideo>());
  container->addWidget(video.get());
  video->addSource(Wt::WLink(mp4Video));
  video->addSource(Wt::WLink(ogvVideo));
  video->setPoster(poster);
  //video->setAlternativeContent(Wt::cpp14::make_unique<Wt::WImage>(poster));
  video->setAlternativeContent(new Wt::WImage(poster));
  video->resize(640, 360);

  //Wt::WText *out = container->addWidget(Wt::cpp14::make_unique<Wt::WText>());
  container->addWidget(out.get());
  std::string str("<p>Video playing</p>");
/*   nameEdit_->enterPressed().connect
    (boost::bind(&VideoApplication::SetText, this, str));
*/
 video->playbackStarted().connect(boost::bind(&VideoApplication::SetText, this, str));
 str.clear();
 str = "<p>Video paused</p>";
 video->playbackStarted().connect(boost::bind(&VideoApplication::SetText, this, str));
 str.clear();
 str = "<p>Volume changed</p>";
 video->playbackStarted().connect(boost::bind(&VideoApplication::SetText, this, str));
 /*video->playbackStarted().connect([this] {
              out->setText("<p>Video playing</p>");
              });
 *//*
  video->playbackPaused().connect([this] {
              out->setText("<p>Video paused</p>");
              });
  video->ended().connect([this] {
              out->setText("<p>Video ended</p>");
              });

  video->volumeChanged().connect([this] {
              out->setText("<p>Volume changed</p>");
              });*/
}

void VideoApplication::SetText(const std::string str)
{
  out->setText(str.c_str());
}



#if 0
/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
VideoApplication::VideoApplication(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Hello world");                               // application title

  root()->addWidget(new WText("Your name, please ? "));  // show some text
  nameEdit_ = new WLineEdit(root());                     // allow text input
  nameEdit_->setFocus();                                 // give focus

  WPushButton *button
    = new WPushButton("Greet me.", root());              // create a button
  button->setMargin(5, Left);                            // add 5 pixels margin

  root()->addWidget(new WBreak());                       // insert a line break

  greeting_ = new WText(root());                         // empty text

  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */

  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */

  /*
   * - using a c++0x lambda:
   */
  // button->clicked().connect(std::bind([=]() {
  //       greeting_->setText("Hello there, " + nameEdit_->text());
  // }));
}
#endif

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new VideoApplication(env);
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

