#pragma once
#include <gtkmm.h>

/**
 * \brief NumberEntry class is a custom Gtk::Entry widget, accepts only numbers.
 * \warning Produces warnings in terminal when non-digit symbol is attempted to be entered, but it doesn't affect functionality
 * \todo Find a way to find different way to block non-digit input (without warning)
 */
class NumberEntry : public Gtk::Entry
{
protected:
	void on_changed() override;
};