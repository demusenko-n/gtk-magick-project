#include <gtkmm/application.h>
#include <Magick++.h>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	Magick::InitializeMagick(nullptr);

	auto app = Gtk::Application::create("mdemusenko.project.example");
	return app->make_window_and_run<MainWindow>(argc, argv);
}