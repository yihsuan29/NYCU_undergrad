<?php
//require_once dirname(__FILE__)."/database_check.php";
$servername="localhost";
$username="root";
$password="";
$database="social_media";

$conn = mysqli_connect($servername,$username,$password,$database);
if(!$conn){
  die("Database connection failed: ".mysqli_connect_error());
}
if(isset($_POST['L_btn'])){

$L_username = htmlspecialchars($_POST['L_username']);
$L_password = htmlspecialchars($_POST['L_password']);


  $sql = "SELECT user_no,username,password,nickname,user_photo FROM username_list WHERE username = '".$L_username."' AND password = '".$L_password."'";
  $result = mysqli_query($conn, $sql); 
  $count = mysqli_num_rows($result);
  

  if($count==1){
    $row = mysqli_fetch_array($result);
    $user_no = $row['user_no'];
    $username = $row['username'];
    $nickname = $row['nickname'];
    $user_photo = $row['user_photo'];
    setcookie("user_no",$user_no,time()+1800,"/");
    setcookie("password",$L_password,time()+1800,"/");
    setcookie("username",$username,time()+1800,"/");
    setcookie("nickname",$nickname,time()+1800,"/");
    setcookie("user_photo",$user_photo,time()+1800,"/");
    echo "success!";
    header("Location:../PersonalHomePage.html");
    
  }else{
    echo "fail";
  }

}

  $conn->close();
?>