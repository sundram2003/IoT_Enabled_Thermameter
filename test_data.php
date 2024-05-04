<?php
date_default_timezone_set('Asia/Kolkata');

// Database connection details
$servername = "localhost";
$username = "root";
$password = "";
$database = "sensordata";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Check if POST data exists for temperature
if (isset($_POST['temperature']) && $_POST['temperature'] !== '') {
  // Extract temperature value from the received string
  $temperatureStr = $_POST['temperature'];
  $temperatureValue = substr($temperatureStr, strpos($temperatureStr, "=") + 1);

  // Convert extracted value to float
  $temperature = floatval($temperatureValue);

  // Get current date/time
  $currentDateTime = date("Y-m-d H:i:s");

  // Prepare and bind the SQL statement with placeholders
  $sql = "INSERT INTO temperature_data (temperature, date_time) VALUES (?, ?)";
  $stmt = $conn->prepare($sql);

  if (!$stmt) {
    echo "Error: " . $conn->error;
  } else {
    // Bind parameters to the prepared statement
    $stmt->bind_param("ss", $temperature, $currentDateTime);

    // Execute the prepared statement
    if ($stmt->execute()) {
      echo "Temperature data inserted successfully: $temperature";
    } else {
      echo "Error: " . $stmt->error;
    }

    // Close the statement
    $stmt->close();
  }
} else {
  echo "Error: Temperature data is missing or empty";
}

// Close the connection
$conn->close();
?>