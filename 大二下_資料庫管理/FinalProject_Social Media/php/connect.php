<?php
function db_connect() {
    $conn = new mysqli("localhost", "root", "", "user");
    if($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    echo "Connected successfully";
}
