#include <Wt/WApplication.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WVideo.h>
#include <memory>


class NewUiApplication : public Wt::WApplication
{
private:
  Wt::WLineEdit *SearchLineEdit;
  Wt::WPushButton *PlayButton;
  Wt::WVideo *VideoPlayer;
  Wt::WText *VideoPlaybackStatus;

  void SetupTheme();
  void SetupHeader();
  void SetupMainBody();
  //void SetupVideoSearchBar();
  void SetupVideoSearchBar(Wt::WContainerWidget *mainLeft);
  void SetupVideoPlayer(Wt::WContainerWidget *mainLeft);
  void SetupFooter();
  void OnPlayButtonPressed();
  void SetVideoPlaybackStatus(const std::string str);
public:
  NewUiApplication(const Wt::WEnvironment& env);
  ~NewUiApplication();
};


