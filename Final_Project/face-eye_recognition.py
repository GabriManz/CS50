import cv2
import os

# Load the pre-trained face classifier
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')

# Create a directory to save images
save_dir = 'images'
os.makedirs(save_dir, exist_ok=True)

# Function to detect faces
def detect_faces(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    return faces

# Function to detect eyes
def detect_eyes(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    eyes = eye_cascade.detectMultiScale(gray, 1.3, 5)
    return eyes

# Open the video capture device (webcam)
vid = cv2.VideoCapture(0)

frame_count = 0

while True:
    # Capture a frame from the video
    ret, frame = vid.read()

    # Detect faces and eyes
    faces = detect_faces(frame)
    eyes = detect_eyes(frame)

    # Draw rectangles around the detected faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)

    # Draw circles around the detected eyes
    for (x, y, w, h) in eyes:
        center = (x + w // 2, y + h // 2)
        radius = min(w, h) // 2
        cv2.circle(frame, center, radius, (0, 0, 255), 2)

    # Display the number of faces and eyes on the frame
    cv2.putText(frame, f'Faces: {len(faces)}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    cv2.putText(frame, f'Eyes: {len(eyes)}', (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    # Display the resulting frame
    cv2.imshow('Video Face Detection', frame)

    # Check if the 's' key is pressed
    key = cv2.waitKey(1) & 0xFF
    if key == ord('s'):
        # Save the image with detections
        save_path = os.path.join(save_dir, f'face_eye_detection_{frame_count}.png')
        cv2.imwrite(save_path, frame)
        print(f'Image saved: {save_path}')
        frame_count += 1
    elif key == ord('q'):
        break

# After the loop, release the capture object
vid.release()
# Close all windows
cv2.destroyAllWindows()
