#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WMediaPlayer>
#include <Wt/WImage>
#include <Wt/WLink>
#include <Wt/WText>
#include <Wt/WVideo>
#include <memory>
#include <string>

// c++0x only, for std::bind
// #include <functional>

using namespace Wt;

class MediaPlayerApplication : public WApplication
{
public:
  MediaPlayerApplication(const WEnvironment& env);

private:
  std::unique_ptr<WContainerWidget> Container;
  std::unique_ptr<WText> OutText;
  std::unique_ptr<WMediaPlayer> MediaPlayer;
  void SetText(const std::string str);
};

MediaPlayerApplication::MediaPlayerApplication(const WEnvironment& env)
  : WApplication(env),
  Container(new Wt::WContainerWidget()),
  OutText(new Wt::WText()),
  MediaPlayer(new Wt::WMediaPlayer(Wt::WMediaPlayer::MediaType::Video))
{
  std::string mp4Video = "https://www.webtoolkit.eu/videos/sintel_trailer.mp4";
  std::string ogvVideo = "https://www.webtoolkit.eu/videos/sintel_trailer.ogv";

  std::string poster = "pics/sintel_trailer.jpg";

  Container->addWidget(MediaPlayer.get());
  MediaPlayer->addSource(Wt::WMediaPlayer::Encoding::M4V, Wt::WLink(mp4Video));
  MediaPlayer->addSource(Wt::WMediaPlayer::Encoding::OGV, Wt::WLink(ogvVideo));
  MediaPlayer->addSource(Wt::WMediaPlayer::Encoding::PosterImage, Wt::WLink(poster));
  MediaPlayer->setTitle("<a href=\"https://durian.blender.org/\""
             "target=\"_blank\">Sintel</a>, (c) copyright Blender Foundation");

  Container->addWidget(OutText.get());
  std::string str("<p>Video playing</p>");
  MediaPlayer->playbackStarted().connect(boost::bind(&MediaPlayerApplication::SetText, this, str));
  str.clear();
  str = "<p>Video paused</p>";
  MediaPlayer->playbackPaused().connect(boost::bind(&MediaPlayerApplication::SetText, this, str));
  str.clear();
  str = "<p>Volume changed</p>";
  MediaPlayer->volumeChanged().connect(boost::bind(&MediaPlayerApplication::SetText, this, str));
  str.clear();
  str = "<p>Video Ended</p>";
  MediaPlayer->ended().connect(boost::bind(&MediaPlayerApplication::SetText, this, str));

  root()->addWidget(Container.get());
}

void MediaPlayerApplication::SetText(const std::string str)
{
  OutText->setText(str.c_str());
}


WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new MediaPlayerApplication(env);
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

