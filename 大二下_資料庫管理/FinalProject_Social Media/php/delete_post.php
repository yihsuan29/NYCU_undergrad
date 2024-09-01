<?php
//require_once dirname(_FILE_)."/connect.php";
setcookie("user_no", "1", time()+1800, "/");
if(isset($_POST['del_post_num']) && isset($_COOKIE["user_no"])) {
    $query = [
        'posts_no' => htmlspecialchars($_POST['del_post_num']),
        'poster_no' => htmlspecialchars($_COOKIE["user_no"]),
    ];
    
    $conn = new mysqli("localhost", "root", "", "social_media");
    if($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    deleteData($query['posts_no'], $query['poster_no'], $conn);
    $conn->close();
}

function deleteData($posts_no, $poster_no, $conn) {
    $sql = "DELETE FROM posts WHERE posts_no='$posts_no' AND poster_no='$poster_no'";
    if(mysqli_query($conn, $sql)) {
        echo "The post is deleted\n";
        echo $posts_no;
    }
    else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
