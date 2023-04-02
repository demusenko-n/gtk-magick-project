#include <iostream>

#include <gtkmm.h>
#include "Image.h"
#include "ImageAsync.h"
#include "MainWindow.h"
#include "Watermark.h"

MainWindow::MainWindow()
	: loadImageButton("Load"),
	  saveImageButton("Save"),
	  rotateButton_("Rotate"),
	  resizeButton_("Resize"),
	  addWatermarkButton_("Add watermark")
{
	auto verticalRightBox =
		Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);

	// configure load/save buttons
	auto buttonsLoadSaveBox =
		Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	buttonsLoadSaveBox->set_homogeneous(true);
	buttonsLoadSaveBox->append(loadImageButton);
	buttonsLoadSaveBox->append(saveImageButton);

	loadImageButton.set_margin(10);
	loadImageButton.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::onLoadClicked));
	saveImageButton.set_margin(10);
	saveImageButton.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::onSaveClicked));
	verticalRightBox->append(*buttonsLoadSaveBox);

	// configure rotate entry & button
	auto rotateBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	rotateDegreesEntry_.set_margin(10);
	rotateDegreesEntry_.set_placeholder_text("degrees");
	rotateBox->append(rotateDegreesEntry_);
	rotateButton_.set_margin(10);
	rotateButton_.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::onRotateClicked));
	rotateBox->append(rotateButton_);
	rotateBox->set_homogeneous(true);
	verticalRightBox->append(*rotateBox);

	// configure resize entries & button
	auto resizeBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	widthEntry_.set_margin(10);
	widthEntry_.set_placeholder_text("width");
	resizeBox->append(widthEntry_);
	heightEntry_.set_margin(10);
	heightEntry_.set_placeholder_text("height");
	resizeBox->append(heightEntry_);
	resizeButton_.set_margin(10);
	resizeButton_.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::onResizeClicked));
	resizeBox->set_homogeneous(true);
	verticalRightBox->append(*resizeBox);
	verticalRightBox->append(resizeButton_);

	// watermark
	addWatermarkButton_.set_margin(10);
	addWatermarkButton_.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::onWatermarkClicked));
	verticalRightBox->append(addWatermarkButton_);

	verticalRightBox->set_size_request(200, 500);
	verticalRightBox->set_expand(false);

	// configure image
	auto imageFrame = Gtk::make_managed<Gtk::Frame>();
	gtkImage_.set_size_request(480, 480);
	imageFrame->set_child(gtkImage_);
	imageFrame->set_margin(10);
	imageFrame->set_expand(true);

	// configure main window
	auto mainBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	set_title("Example");
	mainBox->set_expand(true);
	mainBox->append(*imageFrame);
	mainBox->append(*verticalRightBox);
	set_child(*mainBox);
}

void MainWindow::onLoadClicked()
{
	auto file_chooser = Gtk::make_managed<Gtk::FileChooserDialog>(
		*this, "Choose an image", Gtk::FileChooser::Action::OPEN);
	file_chooser->set_modal(true);
	file_chooser->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	file_chooser->add_button("_Open", Gtk::ResponseType::OK);

	auto filter_img = Gtk::FileFilter::create();
	filter_img->set_name("Images");
	filter_img->add_mime_type("image/png");
	filter_img->add_mime_type("image/jpg");
	filter_img->add_pattern("*.png");
	filter_img->add_pattern("*.jpg");
	file_chooser->add_filter(filter_img);
	file_chooser->signal_response().connect(sigc::bind(
		sigc::mem_fun(*this, &MainWindow::onLoadResponse), file_chooser));
	file_chooser->show();
}

void MainWindow::onLoadResponse(int response_id, Gtk::FileChooserDialog* dialog)
{
	if (response_id != Gtk::ResponseType::OK)
		return;

	const std::string path = dialog->get_file()->get_path();
	delete dialog;

	libImage_.load(path);
	libImage_.setOnImage(gtkImage_);
}

void MainWindow::onSaveClicked()
{
	const auto file_chooser = new Gtk::FileChooserDialog(
		*this, "Save", Gtk::FileChooser::Action::SAVE);
	file_chooser->set_modal(true);
	file_chooser->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	file_chooser->add_button("_Open", Gtk::ResponseType::OK);

	file_chooser->signal_response().connect(sigc::bind(
		sigc::mem_fun(*this, &MainWindow::onSaveResponse), file_chooser));
	file_chooser->show();
}

void MainWindow::onSaveResponse(int response_id, Gtk::FileChooserDialog* dialog)
{
	if (response_id != Gtk::ResponseType::OK)
		return;

	const auto& path = dialog->get_file()->get_path();
	libImage_.save(path);

	delete dialog;
}

void MainWindow::onRotateClicked()
{
	const int number = std::stoi(rotateDegreesEntry_.get_text().raw());
	libImage_.rotate(number);
	libImage_.setOnImage(gtkImage_);
}

void MainWindow::onResizeClicked()
{
	const int width = std::stoi(widthEntry_.get_text().raw());
	const int height = std::stoi(heightEntry_.get_text().raw());

	libImage_.resize(width, height);
	libImage_.setOnImage(gtkImage_);
}

void MainWindow::onWatermarkClicked()
{
	const auto file_chooser = Gtk::make_managed<Gtk::FileChooserDialog>(
		*this, "Choose a watermark image", Gtk::FileChooser::Action::OPEN);
	file_chooser->set_modal(true);
	file_chooser->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	file_chooser->add_button("_Open", Gtk::ResponseType::OK);

	auto filter_img = Gtk::FileFilter::create();
	filter_img->set_name("Images");
	filter_img->add_mime_type("image/png");
	filter_img->add_mime_type("image/jpg");
	filter_img->add_pattern("*.png");
	filter_img->add_pattern("*.jpg");
	file_chooser->add_filter(filter_img);
	file_chooser->signal_response().connect(sigc::bind(
		sigc::mem_fun(*this, &MainWindow::onWatermarkResponse), file_chooser));
	file_chooser->show();
}

void MainWindow::onWatermarkResponse(int response_id,
									 Gtk::FileChooserDialog* dialog)
{
	if (response_id != Gtk::ResponseType::OK)
		return;

	const auto& path = dialog->get_file()->get_path();
	libImage_.addWatermark(path);
	libImage_.setOnImage(gtkImage_);
	delete dialog;
}