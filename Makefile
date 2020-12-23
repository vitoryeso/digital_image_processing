.SUFFIXES:
.SUFFIXES: .cpp

GCC = g++

.cpp:
		#$(GCC) -Wall -Wunused -std=c++11 -O2 $< -o $@ -D CMAKE_BUILD_TYPE=Release -D OPENCV_GENERATE_PKGCONFIG=YES `pkg-config --cflags --libs opencv4`
		$(GCC) -Wall -Wunused -std=c++11 -O2 $< -o $@ -I/usr/include/opencv -L/usr/lib -L/usr/share/opencv/3rdparty/lib -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videoio -lopencv_videostab -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_datasets -lopencv_face -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_surface_matching -lopencv_text -lopencv_tracking -lopencv_xfeatures2d -lopencv_ximgproc -lopencv_xobjdetect -lopencv_xphoto -lrt -ldl -lwebp -lz -lGL -lGLU -ltbb -lpthread

