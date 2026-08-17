This Project is a replica of the Engima Machine. SFML has been used for the GUI

Instructions for setup:

Within the file attached, SFML 3.0 has been included
To get SFML working some alterations need to be made to the C++ linker.

Once in Visual studio 2022 click on the project tab then go into the projects settings.
Make sure configuration at the top of the window is set to All Configuration.
The platform alongside the configuration needs to be set to x64.


Within the C/C++ -> General tab change the Additional Include Directories file path to the include folder within the SFML folder.
Within the Linker -> General tab change Additional Libary Directories file path to the lib folder within the SFML folder.
Within the Linker -> Input tab, additional dependences are listed. Alteration of this is not nessessary unless the steps below apply to you.


The version of SFML attached may not be compatable with your system. Please use this link to install the appropriate version: https://www.sfml-dev.org/download/
Once the correct version has been installed, please use this link to setup up SFML: https://www.sfml-dev.org/tutorials/3.0/getting-started/visual-studio/#introduction



