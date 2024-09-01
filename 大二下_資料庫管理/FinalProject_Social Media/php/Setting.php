<?php
//require_once dirname(__FILE__)."/database_check.php";

$user_no = $_COOKIE["user_no"]; 
$servername="localhost";
$username="root";
$password="";
$database="social_media";

$conn = mysqli_connect($servername,$username,$password,$database);
if(!$conn){
  die("Database connection failed: ".mysqli_connect_error());
}
if(isset($_POST['S_change_name_btn'])){
    if(isset($_POST['S_name'])){
        $S_name = htmlspecialchars($_POST['S_name']);
        if($S_name!=""){
            $sql_name = "UPDATE username_list SET nickname='$S_name' WHERE user_no = '$user_no'";
            $result = mysqli_query($conn,$sql_name);
            setcookie("nickname",'',time()-1800,"/");
            setcookie("nickname",$S_name,time()+1800,"/");
        }
    }
    header("Location:../SettingPage.html");
}


if(isset($_POST['S_change_password_btn'])){
    if(isset($_POST['S_password_check'])&&isset($_POST['S_old_password'])&&isset($_POST['S_new_password'])){
       
        $S_old_password = htmlspecialchars($_POST['S_old_password']);
        $S_new_password = htmlspecialchars($_POST['S_new_password']);
        $S_password_check = htmlspecialchars($_POST['S_password_check']);
        if(($S_old_password!="")&&($S_new_password!="")&&($S_password_check!="")){
            $sql_password = "SELECT password FROM username_list WHERE user_no = '$user_no'";
            $result = mysqli_query($conn, $sql_password);
            $row = mysqli_fetch_array($result);
            if(($row['password']==$S_old_password)&&($S_new_password==$S_password_check)){
                $sql_password_change = "UPDATE username_list SET password='$S_new_password' WHERE user_no = '$user_no'";
                $result_change =mysqli_query($conn,$sql_password_change);
                setcookie("password",'',time()-1800,"/");
                setcookie("password",$S_new_password,time()+1800,"/");
            }else{
                echo "原密碼或確認密碼錯誤";
            }
        }
    }
   header("Location:../SettingPage.html");
}
if(isset($_POST['S_bio_btn'])){
    if(isset($_POST['S_bio'])){
        $S_bio = htmlspecialchars($_POST['S_bio']);
        if($S_bio!=""){
            $sql_bio = "UPDATE username_list SET bio='$S_bio' WHERE user_no ='$user_no'";
            $result = mysqli_query($conn,$sql_bio);
        }
    }
    header("Location:../SettingPage.html");
}
if(isset($_POST['S_photo_name'])){
    $S_photo_name = htmlspecialchars($_POST['S_photo_name']);
    if($S_photo_name!=""){
        
        $S_photo_name = 'img/HeadPhoto/'.$S_photo_name;
        $sql_photo = "UPDATE username_list SET user_photo='$S_photo_name' WHERE user_no = '$user_no'";
        $result =mysqli_query($conn,$sql_photo);
        setcookie("user_photo",'',time()-1800,"/");
        setcookie("user_photo",$S_photo_name,time()+1800,"/");
    }
}

$conn->close();

?>