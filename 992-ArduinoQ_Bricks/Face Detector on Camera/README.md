# Face Detector on Camera

The **Face Detector on Camera** example lets you detect objects on a live feed from a USB camera and visualize bounding boxes around the detections in real-time.

**Note:** This example requires to be run using **Network Mode** in the Arduino App Lab because you will need a USB-C hub and a USB camera.

![Detect Objects on Camera](assets/docs_assets/video-face-detection.png)

This example uses a pre-trained model to detect faces on a live video feed from a camera. The workflow involves continuously getting the frames from a USB camera, processing it through an AI model using the `video_objectdetection` Brick, and displaying the bounding boxes around detected faces. The App is managed from an interactive web interface.

## Brick Used

The example uses the following Bricks:

- `web_ui`: Brick to create a web interface to display the classification results and model controls.
- `video_objectdetection`: Brick to classify faces within a live video feed from a camera.

## Hardware and Software Requirements

### Hardware

- [Arduino® UNO Q](https://store.arduino.cc/products/uno-q)
- USB camera (x1)
- USB-C® hub adapter with external power (x1)
- A power supply (5 V, 3 A) for the USB hub (e.g. a phone charger)
- Personal computer with internet access

### Software

- Arduino App Lab

## How to Use the Example

1. Connect the USB-C hub to the UNO Q and the USB camera.
   ![Hardware setup](assets/docs_assets/hardware-setup.png)
2. Attach the external power supply to the USB-C hub to power everything.
3. Run the App.
   ![Arduino App Lab - Run App](assets/docs_assets/launch-app.png)
4. The App should open automatically in the web browser. You can open it manually via `<board-name>.local:7000`.
5. Position yourself in front of the camera and watch as the App detects your face and say hi.

## How it Works

This example hosts a Web UI where we can see the video input from the camera connected via USB. The video stream is then processed using the `video_objectdetection` Brick. When a face is detected, it is logged along with the confidence score (e.g. 95% face) and show a random greeting.

Here is a brief explanation of the full-stack application:

### 🔧 Backend (`main.py`)

- **Initializes the App Bricks**:
  - **WebUI** (`ui = WebUI()`): provides realtime communication with the frontend.
  - **VideoObjectDetection** (`detection_stream = VideoObjectDetection()`): runs face detection on the live video feed.

- **Detection event wiring**:
  - `on_detect("face", face_detected)`: prints `"Face detected!"` when a face is recognized.
  - `on_detect_all(send_detections_to_ui)`: forwards all detections to the UI as JSON `{ content, confidence, timestamp }`.

- **Controls**:
  - Listens for the `override_th` WebSocket message → dynamically updates the detection confidence threshold.

- **Realtime messaging**:
  - Publishes face detection updates to the frontend with:
    ```python
    ui.send_message("detection", message=entry)
    ```

- **Execution**:
  - Runs with `App.run()`, which maintains the detection stream, WebSocket communication, and callbacks alive.

---

### 💻 Frontend (`index.html` + `app.js`)

- **Video feed**
  - Uses an **iframe** pointing to `/embed` on port `4912`.
  - Auto-retries every second until the camera stream is available.
  - Shows a placeholder while searching for the webcam.

- **Controls**
  - A slider + numeric input + reset button adjust the **confidence threshold** in real-time.
  - Values are sent to the backend via:
    ```javascript
    ui.send_message('override_th', value);
    ```

- **Feedback panel**
  - Displays an animated hand GIF and a random greeting when a face is detected.
  - Resets to a neutral "stars" image after 3 seconds without detections.
  - Includes an **info tooltip** explaining the feedback purpose.

- **Recent detections**
  - Shows up to the last **5 face detections** with:
    - Confidence percentage
    - Timestamp (localized to browser time)
  - If no detections yet, displays a “No face detected yet” placeholder.

- **Connection status**
  - If the WebSocket disconnects, an error banner appears with `"Connection to the board lost. Please check the connection."`.

---

## Understanding the Code

Once the application is running, you can open it in your browser by navigating to `<BOARD-IP-ADDRESS>:7000`. At that point, the device begins performing the following:

- Serving the **face detection UI** and exposing real-time transports.

  The UI is hosted by the `WebUI` Brick and communicates with the backend over WebSocket.  
   The backend pushes detection messages whenever a face is found.

  ```python
  from arduino.app_bricks.web_ui import WebUI
  from arduino.app_bricks.video_objectdetection import VideoObjectDetection
  from datetime import datetime, UTC

  ui = WebUI()
  detection_stream = VideoObjectDetection()

  ui.on_message("override_th",
                lambda sid, threshold: detection_stream.override_threshold(threshold))

  def face_detected():
      print("Face detected!")

  detection_stream.on_detect("face", face_detected)
  detection_stream.on_detect_all(send_detections_to_ui)
  ```

  - `face` (event): triggers the callback printing `"Face detected!"`.
  - `detection` (WebSocket message): JSON entry with label, confidence, and timestamp sent to the UI.
  - `override_th` (WebSocket → backend): dynamically adjusts the minimum confidence threshold.

- Processing detections and broadcasting updates.

  When the model detects faces, the backend:
  1. Iterates over all detected objects and their confidence scores.
  2. Attaches an ISO 8601 UTC timestamp.
  3. Publishes each detection as a JSON entry to the frontend channel `detection`.

  ```python
  def send_detections_to_ui(detections: dict):
      for key, value in detections.items():
          entry = {
              "content": key,
              "confidence": value,
              "timestamp": datetime.now(UTC).isoformat()
          }
          ui.send_message("detection", message=entry)
  ```

- Rendering and interacting on the frontend.

  The **index.html + app.js** bundle defines the interface:
  - A **video iframe** retries `/embed` until the live camera feed is available.
  - A **confidence control** (slider + number + reset) lets the user change the threshold on the fly.
  - A **feedback section** shows greetings with an animated hand when a face is detected.
  - A **recent detections list** displays up to 5 detections with confidence and timestamp.
  - A **connection banner** warns the user if the WebSocket drops.

  ```javascript
  const ui = new WebUI();

  ui.on_message('detection', (message) => {
    printDetection(message); // update detection history
    renderDetections(); // redraw the list
    // updateFeedback is built into app.js
  });
  ```

- Executing the event loop.

  Finally, the backend keeps the whole system alive with:

  ```python
  App.run()
  ```

  This maintains the detection stream, applies confidence threshold overrides, and sustains real-time WebSocket messaging with the frontend.
