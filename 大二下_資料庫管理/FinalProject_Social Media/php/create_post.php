<?php
setcookie("user_no", "1", time()+1800, "/");
if(isset($_POST["P_post_content"]) && isset($_COOKIE["user_no"]) && isset($_POST["P_photo_fname"])) {
    $photo_name = htmlspecialchars($_POST["P_photo_fname"]);
    if($photo_name == "") {
        $photo_name = "fakeimg.png";
    }

    $query = [
        'poster_no' => htmlspecialchars($_COOKIE["user_no"]),
        'content' => htmlspecialchars($_POST["P_post_content"]),
        'picture' => $photo_name,
    ];

    $conn = new mysqli("localhost", "root", "", "social_media");
    if($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    insertData($query['poster_no'], $query['content'], $query['picture'], $conn);
    $conn->close();
}



function insertData($poster_no, $content, $picture, $conn) {
    $nowdate = date("Y-m-d H:i:s");
    $sql = "INSERT INTO posts (poster_no, content, time, picture)
    VALUES ('$poster_no', '$content', '$nowdate', '$picture')";
    if(mysqli_query($conn, $sql)) {
        echo "Your post is created successfully!";
    }
    else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
