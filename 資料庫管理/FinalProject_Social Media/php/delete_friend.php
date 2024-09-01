<?php
//require_once dirname(__FILE__)."/database_check.php";
setcookie("user_no","1",time()+1800,"/") ;
$user_no = $_COOKIE["user_no"]; 
$servername="localhost";
$username="root";
$password="";
$database="social_media";

$conn = mysqli_connect($servername,$username,$password,$database);
if(!$conn){
  die("Database connection failed: ".mysqli_connect_error());
}
else{
    $sql_delete_friend = "SELECT user_no,user_photo,nickname 
                          FROM username_list 
                          WHERE EXISTS(SELECT *
                                       FROM friend_list
                                       WHERE friend_list.user_no = '$user_no'
                                       AND  friend_list.friend_no = username_list.user_no)
                                AND user_no != '$user_no'";
    $result = mysqli_query($conn, $sql_delete_friend);
    while($row =mysqli_fetch_assoc($result))
    {
        $friend[] = array("user_no"     => $row['user_no'],
                        "user_photo"  => $row['user_photo'],
                        "nickname"    => $row['nickname']);
    }
    echo json_encode($friend);
}
?>
