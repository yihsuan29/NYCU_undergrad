function deleteClickID(clickid){
    var delete_user_id = clickid;
    var delete_id = 'delete'+delete_user_id;
    var delete_fr = document.getElementById(delete_id);
    delete_fr.remove();
    window.location.href='/php/delete_friend_result.php?delete_friend_no=' + delete_user_id;
}



