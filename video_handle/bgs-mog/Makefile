export PKG_CONFIG_PATH=/usr/local/AID/pkgconfig:$PKG_CONFIG_PATH
# 20200103
# LDDFLAGS= -lrtspclient -lrockchip_rga -lrockchip_mpp -ldrm -lcam_engine_cifisp -lcam_ia -lpthread  `pkg-config --libs fastcv` `pkg-config --libs gtk+-3.0` 
# INCFLAGS= `pkg-config --cflags fastcv` `pkg-config --cflags gtk+-3.0`
LDDFLAGS= -lrtspclient -lrockchip_rga -lrockchip_mpp -ldrm -lcam_engine_cifisp -lcam_ia -lpthread  `pkg-config --libs bladecv` `pkg-config --libs gtk+-3.0`
INCFLAGS= `pkg-config --cflags bladecv` `pkg-config --cflags gtk+-3.0`
all:
	g++ -c mipi_cam.cpp bgs_mog.cpp bgs_main.cpp ${INCFLAGS} -g -O2
	g++ mipi_cam.o bgs_mog.o bgs_main.o ${LDDFLAGS} -o mog 
