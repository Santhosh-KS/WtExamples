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

  container->addWidget(video.get());
  video->addSource(Wt::WLink(mp4Video));
  video->addSource(Wt::WLink(ogvVideo));
  video->setPoster(poster);
  video->setAlternativeContent(new Wt::WImage(poster));
  video->resize(640, 360);

  container->addWidget(out.get());
  std::string str("<p>Video playing</p>");
  video->playbackStarted().connect(boost::bind(&VideoApplication::SetText, this, str));
  str.clear();
  str = "<p>Video paused</p>";
  video->playbackStarted().connect(boost::bind(&VideoApplication::SetText, this, str));
  str.clear();
  str = "<p>Volume changed</p>";
  video->playbackStarted().connect(boost::bind(&VideoApplication::SetText, this, str));

  root()->addWidget(container.get());
}

void VideoApplication::SetText(const std::string str)
{
  out->setText(str.c_str());
}


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

