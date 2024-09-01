<?php
//require_once dirname(_FILE_)."/connect.php";
setcookie("user_no", "1", time()+1800, "/");
if(isset($_POST['edit_post_num']) && isset($_POST['edit_post_text']) && isset($_COOKIE["user_no"])) {
    $query = [
        'posts_no' => htmlspecialchars($_POST['edit_post_num']),
        'poster_no' => htmlspecialchars($_COOKIE["user_no"]),
        'content' => htmlspecialchars($_POST["edit_post_text"])
    ];
    
    $conn = new mysqli("localhost", "root", "", "social_media");
    if($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    updateData($query['posts_no'], $query['poster_no'], $query['content'], $conn);
    $conn->close();
}


function updateData($post_no, $poster_no, $newcontent, $conn) {
    $sql = "UPDATE posts SET content= '$newcontent' WHERE posts_no='$post_no' AND poster_no='$poster_no'";
    if(mysqli_query($conn, $sql)) {
        echo "Edited successfuly\n";
        echo $poster_no;
        /*要刷新嗎!!!!! 刷新才會load 新的嗎?!!!!*/
    }
    else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
