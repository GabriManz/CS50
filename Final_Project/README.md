#Face and Eye Recognition

##Description:
This project demonstrates real-time face and eye detection using OpenCV's Haar cascades. The application captures video from the webcam, detects faces and eyes, and displays the results on the screen. Additionally, it provides functionality to save images containing the detected faces and eyes.

##How it Works:
1. The program initializes the video capture from the default webcam (index 0).
2. Two Haar cascades, one for face detection and one for eye detection, are loaded.
3. Inside the main loop:
    - Frames are continuously captured from the webcam.
    - Faces and eyes are detected using the Haar cascades.
    - Rectangles are drawn around the detected faces and circles around the detected eyes.
    - The number of faces and eyes is displayed on the video feed.
    - If the 's' key is pressed, the current frame with detections is saved to a directory named 'images'.
    - The loop continues until the 'q' key is pressed.
4. The program releases the video capture object and closes all windows after exiting the loop.

Created by Gabriel Manzano Reche.

References:
https://github.com/opencv/opencv