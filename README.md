# gtk-magick-project
This is very simple sketch of image processing application. 


## The idea is following:
We have Lib::Image and Lib::Watermark, which are wrappers for Magick::Image, 
they implement synchronious implementation of image operations (load, save, resize, rotate, add watermark)
Since this operations can take significant time, in order to avoid blocking of main (gtk) thread, 
this operations should be run in different thread. This is done by ImageAsync class.

vscode, Magick++, gtkmm-4.0, cmake, C++20


This application has some bugs that I'm aware of (for example, it crashes if you try to load non-image file).
But currently I don't have any plans on fixing them.