#include "BusyIndicator.h"
#include "RootController.h"
#include "RootWindow.h"
#include "MechanicalStyle.h"
#include "HomeWidget.h"
#include "StatusBar.h"
#include "WombatDevice.h"
#include "FirstRunWizard.h"
#include "FactoryWidget.h"
#include "NetworkManager.h"
#include "GuiSettingsWidget.h"
#include "TestWizard.h"
#include "KovanSerialBridge.h"
#include "CursorManager.h"
#include "NetworkSettingsWidget.h"
#include <QApplication>
#include <QDir>

#include <QFont>
#include <QFontDatabase>
#include <QSettings>
#include <QStringList>
#include <QTranslator>

int main(int argc, char* argv[])
{ 
	QApplication::setStyle(new MechanicalStyle);
  QApplication::setOrganizationName("KIPR");
  QApplication::setApplicationName("botui");
  
	QApplication app(argc, argv);
  
  QTranslator translator;
  const QString trFile = "botui_" + QSettings().value("locale", "en").toString().left(2);
  qDebug() << "Trying to use translation file " << trFile;
  if(trFile != "botui_en" && translator.load(trFile, "/etc/botui/locale/"))
  {
    qDebug() << "Successfully loaded translation file " << trFile;
    app.installTranslator(&translator);
  }
	
	QDir::setCurrent(QApplication::applicationDirPath());
	qmlRegisterType<BusyIndicator>("ZapBsComponents", 1, 0, "BusyIndicator");
	
	QFontDatabase::addApplicationFont(":/fonts/DejaVuSans-ExtraLight.ttf");
	const int sansFontId = QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
	QFontDatabase::addApplicationFont(":/fonts/DejaVuSansMono.ttf");

	const QStringList sansFamilies = QFontDatabase::applicationFontFamilies(sansFontId);
	if (!sansFamilies.isEmpty()) {
		QFont appFont = QApplication::font();
		appFont.setFamily(sansFamilies.constFirst());
		QApplication::setFont(appFont);
	} else {
		qWarning() << "Unable to load bundled DejaVu Sans font";
	}
	
	srand(time(NULL));
	
	Wombat::Device device;
	CursorManager::ref().setDevice(&device);
	RootWindow rootWindow;
	RootController::ref().initialize(&rootWindow, new HomeWidget(&device));
#ifdef QT_DBUS_LIB
  KovanSerialBridge::ref().init(&device);
  NetworkManager::ref().init(&device);
#endif

	rootWindow.showFullScreen();

	return app.exec();
}
