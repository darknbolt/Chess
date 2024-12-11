 #Chess

This is an implementation of Chess with the use of JNI technology to combine the Swing Library capabilities from Java with C++ quickness for handling game logic.

To setup this project, you must create a header file for Chess.java and load it into your C++ project. Next I recommend for simplicity's sake, using a CMakeList.txt file to link up everything appropriately to create the .dll file. In your Java project you'll need to specify the path to the .dll file (you could copy and paste it into the project but you'll need to keep replacing the old file everytime you make your own adjustments, or download mine).
