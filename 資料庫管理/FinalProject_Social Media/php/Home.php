<?php
// require_once dirname(__FILE__)."/database_check.php";
// require_once dirname(__FILE__)."/login_check.php";
setcookie("user_no", "8", time()+1800, "/");
if(isset($_COOKIE['user_no'])){ // To be confirmed
    // $conn = db_check();
    $servername="localhost";
    $username="root";
    $password="";
    $database="social_media";

    $conn = mysqli_connect($servername, $username, $password, $database);
    if(!$conn){
        die("Database connection failed: ".mysqli_connect_error());
    }

    $user_no = $_COOKIE['user_no'];
    $self_info = getSelfInfo($user_no, $conn);

    $friends_no = getFriendsNo($user_no, $conn); //有朋友的號碼
    $user_array = array();
    while($f = mysqli_fetch_column($friends_no, 0)){
        array_push($user_array, $f);   //朋友的number變成array
    }

    $friend_array = array();
    if($user_array) {
        $friends_info = getFriendsInfo($user_array, $conn); //得到朋友的資訊 from user_list
        while($f = mysqli_fetch_assoc($friends_info)){
            array_push($friend_array, $f);
        }
    }
    
    array_push($user_array, $user_no);
    // echo json_encode($user_array);
    $suggests_info = getSuggestsInfo($user_array, $conn);
    $suggest_array = array();
    while($s = mysqli_fetch_assoc($suggests_info)){
        array_push($suggest_array, $s);
    }

    $posts = getPosts($user_array, $conn);
    $post_array = array();

    while($p = mysqli_fetch_assoc($posts)){
        array_push($post_array, $p);
    }

    echo json_encode(array(
        "post" => $post_array,
        "friend" => array(
            "me" => mysqli_fetch_assoc($self_info),
            "fr" => $friend_array,
            "str" => $suggest_array
            )
        )
    );
    $conn->close();
}

function getFriendsNo($user_no,$conn){
    $sql_friends_no = "SELECT friend_no FROM friend_list WHERE user_no = '$user_no'";
    return mysqli_query($conn, $sql_friends_no);
}
function getSelfInfo($user_no, $conn){
    $sql_self_info = "SELECT user_photo, nickname FROM username_list WHERE user_no = '$user_no'";
    return mysqli_query($conn, $sql_self_info);
}
function getFriendsInfo($user_array, $conn){
    $sql_friends_info = "SELECT user_no, user_photo, nickname FROM username_list ".
    "WHERE user_no IN(".implode(',',$user_array).")";
    return mysqli_query($conn, $sql_friends_info);
}
function getSuggestsInfo($user_array, $conn){
    $sql_suggests_info = "SELECT user_no, user_photo, nickname FROM username_list ".
    "WHERE user_no NOT IN(".implode(',',$user_array).") LIMIT 5";
    return mysqli_query($conn, $sql_suggests_info);
}
function getPosts($user_array, $conn){
    $sql_posts = "SELECT username_list.user_photo, username_list.nickname, posts.time, posts.content, posts.picture ".
    "FROM posts INNER JOIN username_list ON posts.poster_no=username_list.user_no ".
    "WHERE poster_no IN(".implode(',',$user_array).") ORDER BY time DESC";
    return mysqli_query($conn, $sql_posts);
}

?>