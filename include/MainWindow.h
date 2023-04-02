#pragma once
#include <gtkmm.h>
#include "Image.h"
#include "ImageAsync.h"
#include "NumberEntry.h"

class MainWindow : public Gtk::Window
{
public:
	MainWindow();

protected:
	void onLoadClicked();
	void onLoadResponse(int response_id, Gtk::FileChooserDialog* dialog);
	void onSaveClicked();
	void onSaveResponse(int response_id, Gtk::FileChooserDialog* dialog);
	void onRotateClicked();
	void onResizeClicked();
	void onWatermarkClicked();
	void onWatermarkResponse(int response_id, Gtk::FileChooserDialog* dialog);
	void updateImage();

	// async version is used to avoid blocking main thread during manipulating the images
	Lib::ImageAsync libImage_;

	Gtk::Image gtkImage_;

	Gtk::Button loadImageButton;
	Gtk::Button saveImageButton;

	NumberEntry rotateDegreesEntry_;
	Gtk::Button rotateButton_;

	NumberEntry widthEntry_;
	NumberEntry heightEntry_;
	Gtk::Button resizeButton_;

	Gtk::Button addWatermarkButton_;
};
