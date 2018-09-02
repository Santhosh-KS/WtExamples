#include <fstream>
#include <Wt/WMessageBox.h>
#include "NewUi.hpp"

void NewUiApplication::SetupTheme()
{
  setCssTheme("bootstrap3");
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
  // Wt::WContainerWidget *MainDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  // MainDiv->setId("main_left");
  // Wt::WContainerWidget *RowDiv = MainDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
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
  Wt::WContainerWidget *rowDiv = mainLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");
  Wt::WContainerWidget *columnDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnDiv->setStyleClass("col-md-12 col-lg-12 col-xs-6");
  VideoPlayer = columnDiv->addWidget(std::make_unique<Wt::WVideo>());
  VideoPlayer->hide();


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
}

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

  if (url.find("https://www.youtube.com") != std::string::npos
      || url.find("http://www.youtube.com") != std::string::npos)  {
    std::string cmd("python ./ui/scripts/youtube.py -u "); // TODO: Change the path.
    std::string file("/tmp/playablevidlink.txt");
    std::string redirect(" > " + file );
    system((cmd + url + redirect).c_str());
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
  //VideoPlayerDiv->show();
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
  Wt::WContainerWidget *MainDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainDiv->setId("main_left");
  SetupVideoSearchBar(MainDiv);
  SetupVideoPlayer(MainDiv);
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
