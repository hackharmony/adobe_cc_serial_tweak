# Extend trial on Adobe Photoshop CC 2018 (macOS)

	$ mkdir build
	$ cd build
	$ cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<example: /usr/local or $HOME>
	$ cmake --build . --target install
	
Run `adobe_cc_serial_tweak` as a cron job every 6 days so that your trial never expires.

N.B.: On Windows, you need to pass the path of `application.xml` as the first parameter.
