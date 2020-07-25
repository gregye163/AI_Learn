export PKG_CONFIG_PATH=/usr/local/AID/pkgconfig:$PKG_CONFIG_PATH
# // 20200103
# LDDFLAGS= -lrtspclient -lrockchip_rga -lrockchip_mpp -ldrm -lcam_engine_cifisp -lcam_ia -lpthread  `pkg-config --libs fastcv` `pkg-config --libs gtk+-3.0` 
# INCFLAGS= `pkg-config --cflags fastcv` `pkg-config --cflags gtk+-3.0`
LDDFLAGS= -lrtspclient -lrockchip_rga -lrockchip_mpp -ldrm -lcam_engine_cifisp -lcam_ia -lpthread  `pkg-config --libs bladecv` `pkg-config --libs gtk+-3.0`
INCFLAGS= `pkg-config --cflags bladecv` `pkg-config --cflags gtk+-3.0`
all:
	g++ -c -g mipi_cam.cpp image_handle.cpp mipi-demo.cpp ${INCFLAGS}
	g++ -g mipi_cam.o image_handle.o mipi-demo.o ${LDDFLAGS} -o mipi-demo
