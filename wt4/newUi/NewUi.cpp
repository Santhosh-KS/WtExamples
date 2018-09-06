#include <fstream>
#include <signal.h>

#include <Wt/WMessageBox.h>
#include <Wt/WAnchor.h>

#include "NewUi.hpp"

void NewUiApplication::SetupTheme()
{
  //setCssTheme("bootstrap3");
  useStyleSheet(Wt::WLink("css/styleSheet.css")); // TODO: Configurable.
  useStyleSheet(Wt::WLink("resources/themes/bootstrap/3/bootstrap.min.css"));
  //useStyleSheet(Wt::WLink("resources/main.css")); // TODO: Configurable.
}

void NewUiApplication::SetupHeader()
{
  Wt::WContainerWidget *HeaderDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  HeaderDiv->setId("header");
  Wt::WContainerWidget *HeaderDivTextDiv = HeaderDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  HeaderDivTextDiv->setId("h3");
  Wt::WText *HeaderText = HeaderDivTextDiv->addWidget(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("spookfish")));
}

void NewUiApplication::SetupVideoSearchBar(Wt::WContainerWidget *mainLeft)
{
  Wt::WContainerWidget *RowDiv = mainLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
  RowDiv->setStyleClass("row");
  Wt::WContainerWidget *ColumnDiv = RowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ColumnDiv->setStyleClass("col-md-12 col-lg-12 col-xs-6");
  Wt::WContainerWidget *SearchDiv = ColumnDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  SearchDiv->setStyleClass("input-group");
  Wt::WContainerWidget *SearchDivLineEditDiv = SearchDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  SearchLineEdit = SearchDivLineEditDiv->addWidget(std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("Give me Youtube URL")));
  SearchLineEdit->setStyleClass("form-control");
  SearchLineEdit->setFocus();
  Wt::WContainerWidget *ButtonDiv = SearchDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ButtonDiv->setStyleClass("input-group-btn");
  PlayButton = ButtonDiv->addWidget(std::make_unique<Wt::WPushButton>("Play"));
  PlayButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));

  SearchLineEdit->enterPressed().connect
    (std::bind(&NewUiApplication::OnPlayButtonPressed, this));

  PlayButton->clicked().connect(this, &NewUiApplication::OnPlayButtonPressed);
}

void NewUiApplication::SetupVideoPlayer(Wt::WContainerWidget *mainLeft)
{
  MainVideoContainer = mainLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
  Wt::WContainerWidget *rowDiv = MainVideoContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");
  //Wt::WContainerWidget *columnDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  //columnDiv->setStyleClass("col-md-12 col-lg-12 col-xs-6");
  //rowDiv->setId("videoSize");
  Wt::WContainerWidget *columnDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnDiv->setStyleClass("col-md-12 col-lg-12 col-xs-6");
  Wt::WContainerWidget *VideoPlayerDiv = columnDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
//  columnDiv->addWidget(std::make_unique<Wt::WBreak>());
  //VideoPlayerDiv->setId("videoSize");
 // VideoPlayerDiv->setStyleClass("embed-responsive embed-responsive-16by9");
  VideoPlayerDiv->setStyleClass("embed-responsive embed-responsive-4by3");
  VideoPlayer = VideoPlayerDiv->addWidget(std::make_unique<Wt::WVideo>());
  // TODO: Make the Video window responsive to devices.
  //VideoPlayer->setStyleClass("embed-responsive embed-responsive-4by3");
  //VideoPlayer->resize(680, 400);

  VideoPlaybackStatus = columnDiv->addWidget(std::make_unique<Wt::WText>("Playback Not started."));

  std::string str("<p>Video playing</p>");
  VideoPlayer->playbackStarted().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video paused</p>";
  VideoPlayer->playbackPaused().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Volume changed</p>";
  VideoPlayer->volumeChanged().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video Ended</p>";
  VideoPlayer->ended().connect(std::bind(&NewUiApplication::SetVideoPlaybackStatus, this, str));
  MainVideoContainer->hide();
}

void NewUiApplication::SetupImageGallary(Wt::WContainerWidget *mainRight)
{
  Wt::WContainerWidget *gallaryDiv = mainRight->addWidget(std::make_unique<Wt::WContainerWidget>());
  gallaryDiv->setStyleClass("container-fluid");
  Wt::WContainerWidget *rowDiv = gallaryDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");
  Wt::WContainerWidget *columnDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("col-md-2 col-xs-4");
  Wt::WContainerWidget *thumbnailDiv= columnDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  thumbnailDiv->setStyleClass("thumbnail");
  std::string link("images/30/1534569993258_1_30_30_200_200.jpg");
 // Wt::WImage *img = thumbnail->addWidget(std::make_unique<Wt::WContainerWidget>(Wt::WLink(link)));
 // img->setStyleClass("img-responsive ");
  Wt::WLink anchorLink = Wt::WLink(link);
  anchorLink.setTarget(Wt::LinkTarget::NewWindow);
  Wt::WAnchor *anchor = thumbnailDiv->addWidget(std::make_unique<Wt::WAnchor>(anchorLink));
  anchor->addNew<Wt::WImage>(Wt::WLink("images/30/1534569993258_1_30_30_200_200.jpg"));
  Wt::WText *caption = thumbnailDiv->addWidget(std::make_unique<Wt::WText>("Unknown"));
}
#if 0
void NewUiApplication::SetupImageGallary(Wt::WContainerWidget *mainRight)
{
  Wt::WContainerWidget *gallaryDiv = mainRight->addWidget(std::make_unique<Wt::WContainerWidget>());
  gallaryDiv->setStyleClass("container-fluid");
  Wt::WContainerWidget *rowDiv = gallaryDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");
  Wt::WContainerWidget *columnDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnDiv->setStyleClass("col-md-3 col-xs-5");
  ThumbnailDiv = columnDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  //ThumbnailDiv->setStyleClass("thumbnail");
  //std::string link("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/30/1534569964297_1_30_30_200_200.jpg?raw=true");
  std::string link("images/30/1534569993258_1_30_30_200_200.jpg");
  Wt::WContainerWidget *captionDiv = ThumbnailDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  Wt::WText *caption = captionDiv->addWidget(std::make_unique<Wt::WText>("Unknown"));
  Wt::WLink anchorLink = Wt::WLink(link);
  anchorLink.setTarget(Wt::LinkTarget::NewWindow);
  //std::unique_ptr<Wt::WAnchor> anchor = std::make_unique<Wt::WAnchor>(anchorLink);
  Wt::WAnchor *anchor = columnDiv->addWidget(std::make_unique<Wt::WAnchor>(anchorLink));
  anchor->setStyleClass("thumbnail");
  //anchor->addNew<Wt::WImage>(Wt::WLink("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/30/1534569964297_1_30_30_200_200.jpg?raw=true"));
  anchor->addNew<Wt::WImage>(Wt::WLink("images/30/1534569993258_1_30_30_200_200.jpg"));
  captionDiv->setId("caption");
  //captionDiv->addWidget(std::move(anchor));
  //captionDiv->addWidget(anchor);
  Wt::WContainerWidget *captionDiv1 = ThumbnailDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  Wt::WText *caption1 = captionDiv1->addWidget(std::make_unique<Wt::WText>("Unknown"));
  //Wt::WLink anchorLink1 = Wt::WLink("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/30/1534569965471_1_30_30_200_200.jpg?raw=true");
  Wt::WLink anchorLink1 = Wt::WLink("images/30/1534569956644_1_30_30_200_200.jpg");
  anchorLink1.setTarget(Wt::LinkTarget::NewWindow);
  //std::unique_ptr<Wt::WAnchor> anchor1 = std::make_unique<Wt::WAnchor>(anchorLink1);
  Wt::WAnchor *anchor1 = columnDiv->addWidget(std::make_unique<Wt::WAnchor>(anchorLink1));
  //anchor1->addNew<Wt::WImage>(Wt::WLink("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/30/1534569965471_1_30_30_200_200.jpg?raw=true"));
  //anchor1->addNew<Wt::WImage>(Wt::WLink("images/cluster_4.jpg"));
  anchor1->addNew<Wt::WImage>(Wt::WLink("images/30/1534569956644_1_30_30_200_200.jpg"));
  anchor1->setStyleClass("thumbnail");
  captionDiv1->setId("caption");
  //captionDiv1->addWidget(std::move(anchor1));
  //captionDiv1->addWidget(anchor1);

}
#endif
#if 0
void NewUiApplication::SetupImageGallary(Wt::WContainerWidget *mainRight)
{
  Wt::WContainerWidget *gallaryDiv = mainRight->addWidget(std::make_unique<Wt::WContainerWidget>());
  gallaryDiv->setStyleClass("container-fluid");
  Wt::WContainerWidget *rowDiv = gallaryDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");
  Wt::WContainerWidget *columnDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnDiv->setStyleClass("col-md-5 col-xs-3");
  ThumbnailDiv = columnDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ThumbnailDiv->setStyleClass("thumbnail");
  Wt::WImage *img = ThumbnailDiv->addWidget(std::make_unique<Wt::WImage>());
  img->setStyleClass("img-responsive");
  std::string link("images/cluster_0.jpg");
  //std::string link("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/cluster_3.jpg");
  //std::string link("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/cluster_3.jpg?raw=true");
  img->setImageLink(Wt::WLink(link));
  Wt::WContainerWidget *captionDiv = ThumbnailDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  Wt::WText *caption = captionDiv->addWidget(std::make_unique<Wt::WText>("Unknown"));
  //Wt::WAnchor *anchor = captionDiv->addWidget(std::make_unique<Wt::WAnchor>());
  Wt::WLink anchorLink = Wt::WLink(link);
  anchorLink.setTarget(Wt::LinkTarget::NewWindow);
  /*
  std::unique_ptr<Wt::WAnchor> anchor = std::make_unique<Wt::WAnchor>(anchorLink,
                                        "Wt homepage (in a new window)");
  anchor->addNew<Wt::WImage>(Wt::WLink("https://www.emweb.be/css/emweb_small.png"));*/
  //anchor->setLink(anchorLink);
  //Wt::WLink link = Wt::WLink("https://www.emweb.be/");
  //link.setTarget(Wt::LinkTarget::NewWindow);

  std::unique_ptr<Wt::WAnchor> anchor = std::make_unique<Wt::WAnchor>(anchorLink);
  anchor->addNew<Wt::WImage>(Wt::WLink("https://github.com/Santhosh-KS/travis_CI_opencv/blob/master/cluster_3.jpg?raw=true"));

  captionDiv->addWidget(std::move(anchor));
}
#endif

void NewUiApplication::SetupFooter()
{
  Wt::WContainerWidget *FooterDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  FooterDiv->setId("footer");
  Wt::WContainerWidget *FooterDivTextDiv = FooterDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  Wt::WText *Text = FooterDivTextDiv->addWidget(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("© Spookfish. All Rights Reserved.")));
}

// Event and button click handlers.
void NewUiApplication::OnPlayButtonPressed()
{
  auto url(SearchLineEdit->text().toUTF8());
  // little sanity check on the URL.
  std::cout << "OnPlayButtonPressed\n";
  if (url.find("https://www.youtube.com") != std::string::npos
      || url.find("http://www.youtube.com") != std::string::npos)  {
    std::string cmd("python ./ui/scripts/youtube.py -u "); // TODO: Change the path.
    std::string file("/tmp/playablevidlink.txt");
    std::string redirect(" > " + file );
    int ret = system((cmd + url + redirect).c_str());
    if (WIFSIGNALED(ret)
      && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
      return;
    }

    std::ifstream infile(file);
    std::string line;
    while (std::getline(infile, line)) {
      if (!line.empty()) {
        VideoPlayer->show();
        VideoPlayer->clearSources();
        VideoPlayer->addSource(Wt::WLink(line));
        // TODO WARNING:  Creating a thread is not the best way to handle this situation.
        // It is not an optimal solution. If multiple users starts accessing the website;
        // then there will be atleast 1 thread per user/session which will bloat up the
        // system resources and results in very bad end user experiance. Hence this design
        // is not a scalable solution to deploy it as is in the field.
        // This is just a work around to get it running for the demo.
        // Ideally we should span the Video Analyser as a separate Process on a
        // powerful machine and have a pub-sub model to get the work done.
        // Introducing the above mechanism is time consuming and invloves more effort.
        // Hence settling for this approach. This is enough for the demo purpose.
        //std::thread analyzerThread(&NewUiApplication::VideoAnalyzer, this, line);
        //analyzerThread.detach();
        break;
      }
    }
  }
  else {
    VideoPlayer->hide();
    Wt::WMessageBox::show("Information", "Please give me youtube URL.", Wt::StandardButton::Ok);
  }
  //VideoPlayer->show();
  MainVideoContainer->show();
}

void NewUiApplication::SetVideoPlaybackStatus(const std::string str)
{
  VideoPlaybackStatus->setText(str.c_str());
}



NewUiApplication::NewUiApplication(const Wt::WEnvironment& env)
  : WApplication(env)
{
  setTitle("Spookfish UI");                            // application title
  SetupTheme();
  SetupHeader();
  //Wt::WContainerWidget *MainRightDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  //MainRightDiv->setId("main_right");
  //SetupImageGallary(MainRightDiv);
  MainVideoDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainVideoDiv->setId("main_left");
  SetupVideoSearchBar(MainVideoDiv);
  SetupVideoPlayer(MainVideoDiv);
  Wt::WContainerWidget *MainImageGallaryDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainImageGallaryDiv->setId("main_left");
  SetupImageGallary(MainImageGallaryDiv);
  SetupFooter();
/*
  root()->addWidget(std::make_unique<Wt::WText>("Your name, please ? ")); // show some text

  nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>()); // allow text input
  nameEdit_->setFocus();                              // give focus

  auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
                                                      // create a button
  button->setMargin(5, Wt::Side::Left);                   // add 5 pixels margin

  root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line breaki*/
}


NewUiApplication::~NewUiApplication()
{
  // Empty;
}
