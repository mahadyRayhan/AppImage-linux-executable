# AppImage-linux-executable(QT)

To create an AppImage we need some dependencies to be installed.

### AppImage Builder
For Debian/Ubuntu system, we need some dependencies to install AppImage. Run this command to get all the dependencies needed to install AppImage builder.

> sudo apt install -y python3-pip python3-setuptools patchelf desktop-file-utils libgdk-pixbuf2.0-dev fakeroot strace fuse

Next download the appImage toolkit from the github and change the toolkit permission.

> sudo wget https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage -O /usr/local/bin/appimagetool

> sudo chmod +x /usr/local/bin/appimagetool

Now install appImage builder

> sudo pip3 install appimage-builder

### Docker
To install docker you can execute this command:

> sudo apt-get install docker.io

Appimage builder must be able to use docker without root permissions. So, you need to change docker permission. To do that, you can execute the following commands.

> sudo groupadd docker

> sudo usermod -aG docker $USER

If you still have some permission error you may execute this command.
> sudo chmod 666 /var/run/docker.sock

### QT
As this AppImage use QT, so you have to install QT in your system. To install qt, execute the following commands.
> sudo apt-get install build-essential

> sudo apt-get install qtcreator

> sudo apt-get install qt5-default

For my example I use CMake. So you need to install CMake also. You also need git to pull the code from GitHub. To do that, you can execute the following command.

> sudo apt-get install git cmake

depending on your application, you may need more dependency to be installed.

After finishing the dependencies installation open a terminal. Download the sample code from Github. To get the code, execute the following command.

> git clone https://github.com/mahadyRayhan/AppImage-linux-executable

Next enter the directory. Execute following command to go to the project directory:
> cd AppImage-linux-executable

In the folder you will find several files and folders. Folder will look like this.

<pre>
.
├── CMakeLists.txt
├── res
│   ├── CMakeLists.txt
│   ├── hello-world-appimage.desktop
│   └── hello-world-appimage.png
└── src
    ├── CMakeLists.txt
    └── main.cpp

</pre>

Before executing the next commands let me describe the code a little. There are two folders (res(resource) and src) and one CMake file in the project.

#### SRC
In the src folder, there is a main.cpp file, Which is the starting point of our program. This file contains nothing but a "Hello world" print.

There is also a Cmake file in the src(source) directory. It contains a few very basic CMake commands like add_executable(contains program name and starting point) target_link_libraries(where you will include all the necessary libraries you need) and install command.

#### RES
Next res(resource) directory. There are three different files in the res directory. A Cmake file, a .desktop file and .png file. Remember .desktop file and .png file is very important. the desktop file is simply a shortcut that is used to launch applications in Linux. and the png file will be the icon of the project. To create an AppImage, you must have to provide these two file.

Desktop file:
If you open the desktop file, you file find something like this:

<pre>
[Desktop Entry]
Version=1.0
Type=Application
Name=Hello-AppImage-WOrld
Comment=Hello World To AppImage
TryExec=hello-world-appimage
Exec=hello-world-appimage
Icon=hello-world-appimage
MimeType=image/x-foo;
Categories=Utility;
</pre>

1. [Desktop Entry]
> The first line of every desktop file and the section header to identify the block of key-value pairs associated with the desktop. Necessary for the desktop to recognize the file correctly.

2. Version=1.0
> This is the version of your application. In my application, it is 1.0. You can specify any version number you want like 1.0.1 or anything else.

3. Type=Application
> Tells the desktop that this desktop file pertains to an application. Other valid values for this key are Link and Directory.

4. Name=Hello-AppImage-World
> Names of your application for the main menu and any launchers.

5. Comment=Hello word to AppImage
> Describes the application. Used as a tooltip.

6. Exec=hello-world-appimage
> The command that starts this application from a shell. It can have arguments.

7. Icon=hello-world-appimage
> The icon name is associated with this application.

There are some other arguments like **Encoding**, **Terminal**, etc. You can check them from other online sources.

**NOTE: keys are case sensitive. Type=Application is not the same as type=Application or TYPE=Application. Please remember that.**

Cmake file:
This CMake file contains two installation commands. These two command basically said when a package will be generated, where the desktop file and png file should be located.

Now we the final Cmake file which is inside the main folder (not in src or res folder)

This file contains very basic commands like cmake_minimum_required, project(which will be the project name), and add two subdirectories (src and res).

**NOTE: It is not necessary to create 3 separate Cmake file for the program. You can add all the Cmake commands in one file (in the last file, which is outside the src and res folder)**

Now we know have some basic idea about all of our files, lets make the project.
Execute the following command. I build the project in release mode and “/usr” as prefix.

> cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr

Next install the application into AppDir. Execute the following command:

> make install DESTDIR=AppDir

**NOTE: please do not skip installation rules in the CMake file like this "set (CMAKE_SKIP_INSTALL_RULES True)". It will create an error.**

After executing this command, you will have a execuatable in “AppDir/usr/bin/” directory.

### Generating the recipe

Appimage-builder is capable of inspecting the runtime dependencies of a given application to create a recipe for packaging it as AppImage. This can be done using the --generate argument. Execute the following command:

> appimage-builder --generate

The tool will prompt a questionnaire to gather the minimal required information to execute the application. If a desktop entry is found in the AppDir it will be used to fill the fields but you will be able to edit all the values. Make sure of specifying the executable path properly otherwise the execution will fail.

<pre>
INFO:Generator:Searching AppDir
? ID [Eg: com.example.app]: hello-world-appimage
? Application Name: Hello-AppImage-WOrld
? Icon: hello-world-appimage
? Executable path: usr/bin/hello-world-appimage
? Arguments [Default: $@]: $@
? Version [Eg: 1.0.0]: latest
? Update Information [Default: guess]: guess
? Architecture: x86_64
</pre>

### Creating the AppImage
This is the final step of creating an app image. Up until now, if everything works, then we will call the appimage builder to generate the appimage.
While generating the app image, the appimage builder will test the generated app in different platforms like Fedora, Debian, Arch, Centos, etc. If you want to skip this test part you can add --skip-test argument.

The command will be 
> appimage-builder --skip-test

if the process success, you will get a working appimage for your hello-world project and you can run it in any Linux-based system from a terminal or just double-clicking it.

