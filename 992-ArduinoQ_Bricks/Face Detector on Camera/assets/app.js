// SPDX-FileCopyrightText: Copyright (C) Arduino s.r.l. and/or its affiliated companies
//
// SPDX-License-Identifier: MPL-2.0

const recentDetectionsElement = document.getElementById('recentDetections');
const feedbackContentElement = document.getElementById('feedback-content');
const MAX_RECENT_SCANS = 5;
let scans = [];
let detectionTimeout;
let errorContainer = document.getElementById('error-container');
let handVisible = false;

const ui = new WebUI();
ui.on_connect(onUIConnected);
ui.on_disconnect(onUIDisconnected);
ui.on_message('detection', handleDetection);

// Start the application
initializeConfidenceSlider();
feedbackContentElement.innerHTML = `
    <img src="img/stars.svg" alt="Stars">
    <p class="feedback-text">System response will appear here</p>
`;
handVisible = false;
renderDetections();

// Popover logic
const confidencePopoverText =
  'Minimum confidence score for detected faces. Lower values show more results but may include false positives.';
const feedbackPopoverText = 'When camera detects a face, an animation will appear here.';

document.querySelectorAll('.info-btn.confidence').forEach(img => {
  const popover = img.nextElementSibling;
  img.addEventListener('mouseenter', () => {
    popover.textContent = confidencePopoverText;
    popover.style.display = 'block';
  });
  img.addEventListener('mouseleave', () => {
    popover.style.display = 'none';
  });
});

document.querySelectorAll('.info-btn.feedback').forEach(img => {
  const popover = img.nextElementSibling;
  img.addEventListener('mouseenter', () => {
    popover.textContent = feedbackPopoverText;
    popover.style.display = 'block';
  });
  img.addEventListener('mouseleave', () => {
    popover.style.display = 'none';
  });
});

function onUIConnected() {
  if (errorContainer) {
    errorContainer.style.display = 'none';
    errorContainer.textContent = '';
  }
}

function onUIDisconnected() {
  if (errorContainer) {
    errorContainer.textContent = 'Connection to the board lost. Please check the connection.';
    errorContainer.style.display = 'block';
  }
}

function handleDetection(message) {
  if (detectionTimeout) {
    clearTimeout(detectionTimeout);
  }
  printDetection(message);
  renderDetections();

  if (!handVisible) {
    const greetings = [
      'Hello!',
      'Hi there!',
      'Hey!',
      'Nice to see you!',
      'Great to have you here!',
      'I see you',
      'Looking good!',
      'There you are!',
      'Howdy!',
      'Happy to see a face!',
      'Hi, friend!',
      'Face detected!',
      'Hello, human!',
    ];

    const randomGreeting = greetings[Math.floor(Math.random() * greetings.length)];
    feedbackContentElement.innerHTML = `
                <img src="img/hand.gif" alt="Hand">
                <p>${randomGreeting}</p>
            `;
    handVisible = true;
  }

  detectionTimeout = setTimeout(() => {
    feedbackContentElement.innerHTML = `
                <img src="img/stars.svg" alt="Stars">
                <p class="feedback-text">System response will appear here</p>
            `;
    handVisible = false;
  }, 3000); // Revert after 3 seconds of no detections
}

function printDetection(newDetection) {
  scans.unshift(newDetection);
  if (scans.length > MAX_RECENT_SCANS) {
    scans.pop();
  }
}

// Function to render the list of scans
function renderDetections() {
  // Clear the list
  recentDetectionsElement.innerHTML = ``;

  if (scans.length === 0) {
    recentDetectionsElement.innerHTML = `
            <div class="no-recent-scans">
                <img src="./img/no-face.svg">
                No face detected yet
            </div>
        `;
    return;
  }

  scans.forEach(scan => {
    const row = document.createElement('div');
    row.className = 'scan-container';

    // Create a container for content and time
    const cellContainer = document.createElement('span');
    cellContainer.className = 'scan-cell-container cell-border';

    // Content (text + icon)
    const contentText = document.createElement('span');
    contentText.className = 'scan-content';
    const value = scan.confidence;
    const result = Math.floor(value * 1000) / 10;
    contentText.innerHTML = `${result}% - Face`;

    // Time
    const timeText = document.createElement('span');
    timeText.className = 'scan-content-time';
    timeText.textContent = new Date(scan.timestamp).toLocaleString('it-IT').replace(',', ' -');

    // Append content and time to the container
    cellContainer.appendChild(contentText);
    cellContainer.appendChild(timeText);

    row.appendChild(cellContainer);
    recentDetectionsElement.appendChild(row);
  });
}

function initializeConfidenceSlider() {
  const confidenceSlider = document.getElementById('confidenceSlider');
  const confidenceInput = document.getElementById('confidenceInput');
  const confidenceResetButton = document.getElementById('confidenceResetButton');

  confidenceSlider.addEventListener('input', updateConfidenceDisplay);
  confidenceInput.addEventListener('input', handleConfidenceInputChange);
  confidenceInput.addEventListener('blur', validateConfidenceInput);
  updateConfidenceDisplay();

  confidenceResetButton.addEventListener('click', e => {
    if (e.target.classList.contains('reset-icon') || e.target.closest('.reset-icon')) {
      resetConfidence();
    }
  });
}

function handleConfidenceInputChange() {
  const confidenceInput = document.getElementById('confidenceInput');
  const confidenceSlider = document.getElementById('confidenceSlider');

  let value = parseFloat(confidenceInput.value);

  if (isNaN(value)) value = 0.5;
  if (value < 0) value = 0;
  if (value > 1) value = 1;

  confidenceSlider.value = value;
  updateConfidenceDisplay();
}

function validateConfidenceInput() {
  const confidenceInput = document.getElementById('confidenceInput');
  let value = parseFloat(confidenceInput.value);

  if (isNaN(value)) value = 0.5;
  if (value < 0) value = 0;
  if (value > 1) value = 1;

  confidenceInput.value = value.toFixed(2);

  handleConfidenceInputChange();
}

function updateConfidenceDisplay() {
  const confidenceSlider = document.getElementById('confidenceSlider');
  const confidenceInput = document.getElementById('confidenceInput');
  const confidenceValueDisplay = document.getElementById('confidenceValueDisplay');
  const sliderProgress = document.getElementById('sliderProgress');

  const value = parseFloat(confidenceSlider.value);
  ui.send_message('override_th', value); // Send confidence to backend
  const percentage = ((value - confidenceSlider.min) / (confidenceSlider.max - confidenceSlider.min)) * 100;

  const displayValue = value.toFixed(2);
  confidenceValueDisplay.textContent = displayValue;

  if (document.activeElement !== confidenceInput) {
    confidenceInput.value = displayValue;
  }

  sliderProgress.style.width = percentage + '%';
  confidenceValueDisplay.style.left = percentage + '%';
}

function resetConfidence() {
  const confidenceSlider = document.getElementById('confidenceSlider');
  const confidenceInput = document.getElementById('confidenceInput');

  confidenceSlider.value = '0.5';
  confidenceInput.value = '0.50';
  updateConfidenceDisplay();
}
