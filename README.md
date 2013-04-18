uqq - QQ client for ubuntu phone

QQ is a popular chat app in China. 
uqq is QQ client developed for ubuntu phone. If you want to try this app, first you must have a QQ number (or you can register from the official website: http://zc.qq.com/en/index.html), 

the demo video on youtube:
https://www.youtube.com/watch?v=o99vtgglVWA

please follow the below instructions:

1. install the ubuntu-sdk:

$ sudo add-apt-repository ppa:canonical-qt5-edgers/qt5-proper && sudo add-apt-repository ppa:ubuntu-sdk-team/ppa && sudo apt-get update && sudo apt-get install ubuntu-sdk notepad-qml
$ sudo apt-get install gstreamer0.10-plugins-bad

You can find more detail about the ubuntu-sdk in the official page: http://developer.ubuntu.com/get-started/gomobile/.

2. get this app source code:
$ git clone git://github.com/ginuerzh/uqq.git

3. run:
$ cd uqq
$ sh uqq.sh

After compiling, if no error occurs, then you should see the main window.

any questions? send to ginuerzh@gmail.com please.


