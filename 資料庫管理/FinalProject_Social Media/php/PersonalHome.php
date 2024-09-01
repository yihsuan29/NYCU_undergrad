<?php
// require_once dirname(__FILE__)."/database_check.php";
// require_once dirname(__FILE__)."/login_check.php";

// $user_no = $_COOKIE["user_no"];
$servername="localhost";
$username="root";
$password="";
$database="social_media";

$conn = mysqli_connect($servername,$username,$password,$database);
if(!$conn){
    die("Database connection failed: ".mysqli_connect_error());
}

if(isset($_GET['user_no'])){ // To be confirmed
    // $conn = db_check();
    $user_no = $_GET['user_no'];
    $info = getInfo($user_no,$conn);
    $contents = getContents($user_no,$conn);
    $content_array = array();
    while($c = mysqli_fetch_assoc($contents)){
        array_push($content_array, $c);
    }
    echo json_encode(array(
        "info" => mysqli_fetch_assoc($info),
        "content" => $content_array
        )
    );
}
if(isset($_GET['post_no'])){ // To be confirmed
    // $conn = db_check();
    $post_no = $_GET['post_no'];
    $pop_post = getPost($post_no,$conn);
    echo json_encode(mysqli_fetch_assoc($pop_post));
}

function getInfo($user_no,$conn){
    $sql_info = "SELECT nickname, bio, user_photo FROM username_list WHERE user_no = '$user_no'";
    return mysqli_query($conn,$sql_info);
}
function getContents($user_no,$conn){
    $sql_contents = "SELECT post_no, picture FROM post_data WHERE poster_no = '$user_no'";
    return mysqli_query($conn,$sql_contents);
}
function getPost($post_no,$conn){
    $sql_post = "SELECT content, time FROM post_data WHERE post_no = '$post_no'";
    return mysqli_query($conn,$sql_post);
}
$conn->close();
?>