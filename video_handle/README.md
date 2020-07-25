编译:
1, encoder-decoder-demo
	cd encoder-decoder-demo, 执行make -j2生成enc-demo
	sudo ./enc-demo -i 0 生成test.264
	sudo ./enc-demo -i 0 -l 可以调出摄像头

2, bgs-mog
	cd bgs-mog
	make
	./mog -t usb -m 0


3, image_handle:
	cd image_handle
	make -j2
	./mipi_demo -t usb -m 0 -s 6
	-t从哪里选择, -m 第几个设备, -s 代码中的哪项操作
